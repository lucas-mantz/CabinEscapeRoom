// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleBase.h"
#include "BookshelfPuzzle.generated.h"

class APullableBook;
class AHingedInteractable;
class AInventoryPickup;

UCLASS()
class CABINESCAPEROOM_API ABookshelfPuzzle : public APuzzleBase
{
	GENERATED_BODY()

public:
	ABookshelfPuzzle();

	void RegisterBook(APullableBook* Book);
	void TryBook(APullableBook* Book);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookshelf")
	int32 CurrentStep = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bookshelf")
	int32 RequiredBookCount = 4;

	UPROPERTY()
	TArray<TObjectPtr<APullableBook>> Books;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bookshelf|Reward")
	TObjectPtr<AHingedInteractable> SecretCompartment;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Bookshelf|Reward")
	TObjectPtr<AInventoryPickup> RewardPickup;

	void ResetPuzzle();
};
