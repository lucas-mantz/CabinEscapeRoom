// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "FuseBoxPuzzle.h"
#include "FuseBreaker.generated.h"

class UStaticMeshComponent;
class USoundBase;

UCLASS()
class CABINESCAPEROOM_API AFuseBreaker : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFuseBreaker();

	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual FText GetInteractionText_Implementation() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breaker")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breaker")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breaker")
	TObjectPtr<USceneComponent> LeverPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breaker")
	TObjectPtr<UStaticMeshComponent> LeverMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Breaker")
	TObjectPtr<AFuseBoxPuzzle> FuseBoxPuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Breaker")
	EFuseCircuit Circuit = EFuseCircuit::Lights;

	FRotator StartingRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Breaker|Visual")
	FRotator RotationAmount = FRotator(105.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> InteractionSound;

	void UpdateBreakerVisual();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
