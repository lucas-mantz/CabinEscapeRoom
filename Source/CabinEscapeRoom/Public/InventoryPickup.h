// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InventoryComponent.h"
#include "InventoryPickup.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;

UCLASS()
class CABINESCAPEROOM_API AInventoryPickup
	: public AActor,
	  public IInteractableInterface
{
	GENERATED_BODY()

public:
	AInventoryPickup();

	virtual void Interact_Implementation(AActor* Interactor) override;

	virtual FText GetInteractionText_Implementation()
		const override;

	// Used by puzzles to enable/disable the reward
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetPickupEnabled(bool bEnabled);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UBoxComponent> InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FInventoryItem ItemData;

	// Normal pickups = true
	// Puzzle rewards like the fireplace poker = false
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool bStartsEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> PickupFailedSound;

private:
	bool bPickupEnabled = true;
};