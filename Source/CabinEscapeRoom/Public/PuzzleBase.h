// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBase.generated.h"

class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleCompleted);

UCLASS()
class CABINESCAPEROOM_API APuzzleBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleBase();

	UFUNCTION(BlueprintPure, Category = "Puzzle")
	bool IsSolved() const;

	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
	FOnPuzzleCompleted OnPuzzleCompleted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Puzzle")
	TObjectPtr<USoundBase> IncorrectSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Puzzle")
	TObjectPtr<USoundBase> PuzzleSolvedSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Puzzle")
	bool bSolved = false;

	void PlayIncorrectSound() const;

	virtual void CompletePuzzle();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
