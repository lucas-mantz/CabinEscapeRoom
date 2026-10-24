// Fill out your copyright notice in the Description page of Project Settings.

#include "HingedInteractable.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

AHingedInteractable::AHingedInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(Root);

	Hinge = CreateDefaultSubobject<USceneComponent>(TEXT("Hinge"));
	Hinge->SetupAttachment(Root);

	MovingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MovingMesh"));
	MovingMesh->SetupAttachment(Hinge);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(Hinge);
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AHingedInteractable::BeginPlay()
{
	Super::BeginPlay();

	ClosedRotation = Hinge->GetRelativeRotation();
	TargetRotation = ClosedRotation;
}

void AHingedInteractable::Interact_Implementation(AActor* Interactor)
{
	if (!Interactor) return;

	if (bLocked)
	{
		UInventoryComponent* Inventory = Interactor->FindComponentByClass<
			UInventoryComponent>();

		if (RequiredItemId.IsNone() || !Inventory || !Inventory->HasItem(RequiredItemId))
		{
			if (LockedSound)
			{
				UGameplayStatics::PlaySoundAtLocation(
					this,
					LockedSound,
					GetActorLocation()
				);
			}

			return;
		}

		if (bConsumeRequiredItem) Inventory->RemoveItem(RequiredItemId);

		bLocked = false;
	}

	if (bIsOpen)
	{
		if (bCanClose) Close();

		return;
	}

	Open();
}

FText AHingedInteractable::GetInteractionText_Implementation() const
{
	if (bLocked) return LockedText;

	if (bIsOpen)
	{
		if (bCanClose) return CloseText;
		return FText::GetEmpty();
	}

	return OpenText;
}

void AHingedInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Hinge) return;

	const FRotator CurrentRotation = Hinge->GetRelativeRotation();

	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, OpenSpeed);

	Hinge->SetRelativeRotation(NewRotation);
}

void AHingedInteractable::Open()
{
	if (bIsOpen) return;

	bIsOpen = true;

	TargetRotation = ClosedRotation + OpenRotationOffset;

	if (OpenSound) UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
}

void AHingedInteractable::Close()
{
	if (!bIsOpen) return;

	bIsOpen = false;

	TargetRotation = ClosedRotation;

	if (CloseSound) UGameplayStatics::PlaySoundAtLocation(this, CloseSound, GetActorLocation());
}