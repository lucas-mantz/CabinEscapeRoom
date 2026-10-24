// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "HingedInteractable.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;

UCLASS()
class CABINESCAPEROOM_API AHingedInteractable
	: public AActor,
	  public IInteractableInterface
{
	GENERATED_BODY()

public:
	AHingedInteractable();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* Interactor) override;

	virtual FText GetInteractionText_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category = "Hinged Object")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "Hinged Object")
	void Close();

protected:
	virtual void BeginPlay() override;

	// Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hinged Object")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hinged Object")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hinged Object")
	TObjectPtr<USceneComponent> Hinge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hinged Object")
	TObjectPtr<UStaticMeshComponent> MovingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hinged Object")
	TObjectPtr<UBoxComponent> InteractionBox;

	// Movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Movement")
	FRotator OpenRotationOffset = FRotator(0.0f, 90.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Movement")
	float OpenSpeed = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Movement")
	bool bCanClose = false;

	// Locking

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Lock")
	bool bLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Lock")
	FName RequiredItemId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Lock")
	bool bConsumeRequiredItem = true;

	// Interaction text

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Interaction")
	FText OpenText = FText::FromString(TEXT("[E] Open"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Interaction")
	FText CloseText = FText::FromString(TEXT("[E] Close"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hinged Object|Interaction")
	FText LockedText = FText::FromString(TEXT("[E] Locked"));

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<USoundBase> OpenSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<USoundBase> CloseSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<USoundBase> LockedSound;

private:
	bool bIsOpen = false;

	FRotator ClosedRotation;
	FRotator TargetRotation;
};