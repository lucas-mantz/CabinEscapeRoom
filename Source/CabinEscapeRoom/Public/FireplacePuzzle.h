// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleBase.h"
#include "InteractableInterface.h"
#include "FireplacePuzzle.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UNiagaraComponent;
class UPointLightComponent;
class USoundBase;
class AHingedInteractable;

UENUM(BlueprintType)
enum class EFireplaceStage : uint8
{
	Empty,
	WoodPlaced,
	TinderPlaced,
	Lit,
	Completed
};

UCLASS()
class CABINESCAPEROOM_API AFireplacePuzzle
	: public APuzzleBase,
	  public IInteractableInterface
{
	GENERATED_BODY()

public:
	AFireplacePuzzle();

	virtual void Interact_Implementation(AActor* Interactor) override;

	virtual FText GetInteractionText_Implementation()
		const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FireplaceMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> InteractionBox;

	// Objects that become visible as the player builds the fire.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PlacedFirewoodMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PlacedNewspaperMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> FireEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPointLightComponent> FireLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fireplace")
	EFireplaceStage CurrentStage = EFireplaceStage::Empty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Fireplace")
	TObjectPtr<USoundBase> FirewoodPlacedSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Fireplace")
	TObjectPtr<USoundBase> NewspaperPlacedSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Fireplace")
	TObjectPtr<USoundBase> FireLitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Fireplace")
	TObjectPtr<USoundBase> FireStokedSound;

	// Inventory IDs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fireplace|Items")
	FName FirewoodItemId = TEXT("Firewood");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fireplace|Items")
	FName NewspaperItemId = TEXT("Newspaper");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fireplace|Items")
	FName MatchesItemId = TEXT("Matches");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fireplace|Items")
	FName PokerItemId = TEXT("FireplacePoker");

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Fireplace|Completion")
	TObjectPtr<AHingedInteractable> LeftExitDoor;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Fireplace|Completion")
	TObjectPtr<AHingedInteractable> RightExitDoor;

private:
	void PlaceFirewood(AActor* Interactor);
	void PlaceNewspaper(AActor* Interactor);
	void LightFire(AActor* Interactor);
	void StokeFire(AActor* Interactor);
};