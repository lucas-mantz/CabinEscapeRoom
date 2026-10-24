// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APuzzleBase::APuzzleBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APuzzleBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APuzzleBase::IsSolved() const
{
	return bSolved;
}

void APuzzleBase::PlayIncorrectSound() const
{
	if (IncorrectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			IncorrectSound,
			GetActorLocation()
		);
	}
}

void APuzzleBase::CompletePuzzle()
{
	if (bSolved) return;

	bSolved = true;

	if (PuzzleSolvedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			PuzzleSolvedSound,
			GetActorLocation()
		);
	}

	OnPuzzleCompleted.Broadcast();
}
