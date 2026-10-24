// Copyright Epic Games, Inc. All Rights Reserved.

#include "CabinEscapeRoomCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractableInterface.h"
#include "DrawDebugHelpers.h"
#include "CabinEscapeRoomPlayerController.h"
#include "InventoryComponent.h"

void ACabinEscapeRoomCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(FName("Head"), EPhysBodyOp::PBO_None);
}

ACabinEscapeRoomCharacter::ACabinEscapeRoomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(20.0f, 0.0f, 80.0f), FRotator::ZeroRotator);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	FirstPersonMesh->SetVisibility(false);

	// configure the character comps
	GetMesh()->SetOwnerNoSee(false);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	// Inventory Component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void ACabinEscapeRoomCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACabinEscapeRoomCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACabinEscapeRoomCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACabinEscapeRoomCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACabinEscapeRoomCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ACabinEscapeRoomCharacter::LookInput);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACabinEscapeRoomCharacter::TryInteract);
	}
}

void ACabinEscapeRoomCharacter::MoveInput(const FInputActionValue &Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ACabinEscapeRoomCharacter::LookInput(const FInputActionValue &Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);
}

void ACabinEscapeRoomCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ACabinEscapeRoomCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ACabinEscapeRoomCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ACabinEscapeRoomCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ACabinEscapeRoomCharacter::TryInteract()
{
	if (!FirstPersonCameraComponent)
		return;

	const FVector Start = FirstPersonCameraComponent->GetComponentLocation();

	const FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * InteractionDistance;

	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	if (!bHit)
		return;

	AActor *HitActor = HitResult.GetActor();

	if (!HitActor)
		return;

	if (HitActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		IInteractableInterface::Execute_Interact(HitActor, this);
}

void ACabinEscapeRoomCharacter::UpdateInteractionPrompt()
{
	if (!FirstPersonCameraComponent)
		return;

	const FVector Start = FirstPersonCameraComponent->GetComponentLocation();

	const FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * InteractionDistance;

	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	ACabinEscapeRoomPlayerController *PlayerController = Cast<ACabinEscapeRoomPlayerController>(GetController());

	if (!PlayerController)
		return;

	// Nothing hit
	if (!bHit)
	{
		PlayerController->HideInteractionPrompt();
		return;
	}

	AActor *HitActor = HitResult.GetActor();

	if (!HitActor)
	{
		PlayerController->HideInteractionPrompt();
		return;
	}

	// Actor is not interactable
	if (!HitActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		PlayerController->HideInteractionPrompt();
		return;
	}

	// Ask the interactable what its prompt should say
	const FText InteractionText = IInteractableInterface::Execute_GetInteractionText(HitActor);

	if (InteractionText.IsEmpty())
	{
		PlayerController->HideInteractionPrompt();
		return;
	}

	PlayerController->ShowInteractionPrompt(InteractionText);
}

void ACabinEscapeRoomCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	UpdateInteractionPrompt();
}