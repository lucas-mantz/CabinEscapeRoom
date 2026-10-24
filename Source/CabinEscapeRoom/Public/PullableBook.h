// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "PullableBook.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;
class ABookshelfPuzzle;

UCLASS()
class CABINESCAPEROOM_API APullableBook : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APullableBook();

	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual FText GetInteractionText_Implementation() const override;

	int32 GetCorrectOrder() const
	{
		return CorrectOrder;
	}
	void SetPulled(bool bPulled);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Book")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Book")
	TObjectPtr<UStaticMeshComponent> BookMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Book")
	TObjectPtr<UBoxComponent> InteractionBox;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Book")
	TObjectPtr<ABookshelfPuzzle> BookshelfPuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
	int32 CorrectOrder = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book|Animation")
	FVector PullOffset = FVector(15.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book|Animation")
	float PullSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> InteractionSound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsPulled = false;

	FVector StartingLocation;
	FVector TargetLocation;
};
