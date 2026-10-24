// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleBase.h"
#include "InteractableInterface.h"
#include "CombinationLockBox.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS()
class CABINESCAPEROOM_API ACombinationLockBox : public APuzzleBase, public IInteractableInterface
{
	GENERATED_BODY()

public:
	ACombinationLockBox();

	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual FText GetInteractionText_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category = "Lockbox")
	void SetDigit(int32 DigitIndex, int32 value);

	UFUNCTION(BlueprintCallable, Category = "Lockbox")
	void IncrementDigit(int32 DigitIndex);

	UFUNCTION(BlueprintCallable, Category = "Lockbox")
	void SubmitCode();

	UFUNCTION(BlueprintPure, Category = "Lockbox")
	int32 GetDigit(int32 DigitIndex) const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lockbox")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lockbox")
	TObjectPtr<UStaticMeshComponent> BoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lockbox")
	TObjectPtr<USceneComponent> LidHinge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lockbox")
	TObjectPtr<UStaticMeshComponent> LidMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lockbox|Code")
	TArray<int32> CorrectCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lockbox|Code")
	TArray<int32> CurrentCode;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lockbox|Reward")
	TObjectPtr<AActor> RewardActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lockbox|Lid")
	FRotator OpenRotationOffset = FRotator(0.0f, 100.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lockbox|Lid")
	float OpenSpeed = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> InteractionSound;

private:
	FRotator ClosedRotation;
	FRotator TargetRotation;

	void OpenLid();
	bool IsEnteredCodeCorrect() const;
};
