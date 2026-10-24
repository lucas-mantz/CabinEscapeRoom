// Fill out your copyright notice in the Description page of Project Settings.

#include "CombinationLockBox.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CabinEscapeRoomPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

ACombinationLockBox::ACombinationLockBox()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(Root);

	LidHinge = CreateDefaultSubobject<USceneComponent>(TEXT("LidHinge"));
	LidHinge->SetupAttachment(Root);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(LidHinge);

	CurrentCode.Init(0, 4);
	CorrectCode = {1, 2, 3, 4};
}

void ACombinationLockBox::BeginPlay()
{
	Super::BeginPlay();

	ClosedRotation = LidHinge->GetRelativeRotation();
	TargetRotation = ClosedRotation;

	if (RewardActor)
	{
		RewardActor->SetActorHiddenInGame(true);
		RewardActor->SetActorEnableCollision(false);
	}
}

void ACombinationLockBox::SetDigit(int32 DigitIndex, int32 Value)
{
	if (bSolved) return;
	if (!CurrentCode.IsValidIndex(DigitIndex)) return;

	CurrentCode[DigitIndex] = FMath::Clamp(Value, 0, 9);
}

int32 ACombinationLockBox::GetDigit(int32 DigitIndex) const
{
	if (!CurrentCode.IsValidIndex(DigitIndex)) return 0;
	return CurrentCode[DigitIndex];
}

void ACombinationLockBox::IncrementDigit(int32 DigitIndex)
{
	if (bSolved) return;
	if (!CurrentCode.IsValidIndex(DigitIndex)) return;

	CurrentCode[DigitIndex] = (CurrentCode[DigitIndex] + 1) % 10;
}

bool ACombinationLockBox::IsEnteredCodeCorrect() const
{
	if (CurrentCode.Num() != CorrectCode.Num()) return false;

	for (int32 i = 0; i < CurrentCode.Num(); i++)
	{
		if (CurrentCode[i] != CorrectCode[i]) return false;
	}

	return true;
}

void ACombinationLockBox::SubmitCode()
{
	if (bSolved) return;

	if (!IsEnteredCodeCorrect())
	{
		PlayIncorrectSound();
		return;
	}

	CompletePuzzle();

	OpenLid();
}

void ACombinationLockBox::OpenLid()
{
	TargetRotation = ClosedRotation + OpenRotationOffset;

	if (RewardActor)
	{
		RewardActor->SetActorHiddenInGame(false);
		RewardActor->SetActorEnableCollision(true);
	}
}

void ACombinationLockBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FRotator CurrentRotation = LidHinge->GetRelativeRotation();
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, OpenSpeed);

	LidHinge->SetRelativeRotation(NewRotation);
}

void ACombinationLockBox::Interact_Implementation(AActor* Interactor)
{
	if (bSolved || !Interactor) return;

	APawn* Pawn = Cast<APawn>(Interactor);

	if (!Pawn) return;

	ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(Pawn->GetController());

	if (!Controller) return;

	Controller->ShowLockBox(this);

	if (InteractionSound) UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
}

FText ACombinationLockBox::GetInteractionText_Implementation() const
{
	if (bSolved) return FText::GetEmpty();

	return FText::FromString(TEXT("[E] Inspect Lockbox"));
}
