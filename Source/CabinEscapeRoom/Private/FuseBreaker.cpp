// Fill out your copyright notice in the Description page of Project Settings.

#include "FuseBreaker.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFuseBreaker::AFuseBreaker()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(Root);

	LeverPivot = CreateDefaultSubobject<USceneComponent>(TEXT("LeverPivot"));
	LeverPivot->SetupAttachment(Root);

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	LeverMesh->SetupAttachment(LeverPivot);
}

// Called when the game starts or when spawned
void AFuseBreaker::BeginPlay()
{
	Super::BeginPlay();

	StartingRotation = LeverPivot->GetRelativeRotation();
}

// Called every frame
void AFuseBreaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFuseBreaker::Interact_Implementation(AActor* Interactor)
{
	if (!FuseBoxPuzzle)
	{
		return;
	}

	if (FuseBoxPuzzle->IsSolved()) return;

	FuseBoxPuzzle->ToggleCircuit(Circuit);

	UpdateBreakerVisual();

	if (InteractionSound) UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
}

void AFuseBreaker::UpdateBreakerVisual()
{

	if (!FuseBoxPuzzle || !LeverPivot) return;

	const bool bIsOn = FuseBoxPuzzle->IsCircuitOn(Circuit);

	if (bIsOn) LeverPivot->SetRelativeRotation(StartingRotation + RotationAmount);
	else
		LeverPivot->SetRelativeRotation(StartingRotation);
}

FText AFuseBreaker::GetInteractionText_Implementation() const
{

	if (!FuseBoxPuzzle) return FText::GetEmpty();

	switch (Circuit)
	{
	case EFuseCircuit::Lights:
		return FText::FromString(TEXT("[E] Toggle Lights"));
	case EFuseCircuit::Bedroom:
		return FText::FromString(TEXT("[E] Toggle Bedroom"));
	case EFuseCircuit::Heater:
		return FText::FromString(TEXT("[E] Toggle Heater"));
	case EFuseCircuit::Security:
		return FText::FromString(TEXT("[E] Toggle Security"));

	default:
		return FText::FromString(TEXT("[E] Toggle Breaker"));
	}
}
