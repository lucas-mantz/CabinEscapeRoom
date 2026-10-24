// Fill out your copyright notice in the Description page of Project Settings.

#include "PullableBook.h"
#include "BookshelfPuzzle.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APullableBook::APullableBook()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BookMesh"));
	BookMesh->SetupAttachment(Root);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(Root);
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void APullableBook::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = BookMesh->GetRelativeLocation();

	TargetLocation = StartingLocation;

	if (BookshelfPuzzle) BookshelfPuzzle->RegisterBook(this);
}

void APullableBook::Interact_Implementation(AActor* Interactor)
{
	if (!BookshelfPuzzle)
	{
		return;
	}

	const bool bCanInteract = !bIsPulled && !BookshelfPuzzle->IsSolved();
	if (bCanInteract && InteractionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			InteractionSound,
			GetActorLocation()
		);
	}

	BookshelfPuzzle->TryBook(this);
}

// Called every frame
void APullableBook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!BookMesh) return;

	const FVector NewLocation = FMath::VInterpTo(BookMesh->GetRelativeLocation(), TargetLocation, DeltaTime, PullSpeed);

	BookMesh->SetRelativeLocation(NewLocation);
}

FText APullableBook::GetInteractionText_Implementation() const
{
	if (bIsPulled) return FText::GetEmpty();

	return FText::FromString(TEXT("[E] Pull Book"));
}

void APullableBook::SetPulled(bool bPulled)
{
	bIsPulled = bPulled;

	if (bIsPulled) TargetLocation = StartingLocation + PullOffset;
	else
		TargetLocation = StartingLocation;
}