// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CabinPowerController.generated.h"

class ALight;

UCLASS()
class CABINESCAPEROOM_API ACabinPowerController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACabinPowerController();

	UFUNCTION(BlueprintCallable, Category = "Power")
	void TurnPowerOn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Power")
	TArray<TObjectPtr<ALight>> CabinLights;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Power|Fuse Box")
	TObjectPtr<ALight> RedIndicatorLight;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Power|Fuse Box")
	TObjectPtr<ALight> GreenIndicatorLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Power")
	bool bPoweredOn = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
