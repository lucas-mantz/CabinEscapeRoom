// Fill out your copyright notice in the Description page of Project Settings.

#include "CabinPowerController.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"

// Sets default values
ACabinPowerController::ACabinPowerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACabinPowerController::BeginPlay()
{
	Super::BeginPlay();

	for (ALight* Light : CabinLights)
	{
		if (Light && Light->GetLightComponent()) Light->GetLightComponent()->SetVisibility(false);
	}

	if (RedIndicatorLight && RedIndicatorLight->GetLightComponent()) RedIndicatorLight->GetLightComponent()->SetVisibility(true);

	if (GreenIndicatorLight && GreenIndicatorLight->GetLightComponent()) GreenIndicatorLight->GetLightComponent()->SetVisibility(false);
}

// Called every frame
void ACabinPowerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACabinPowerController::TurnPowerOn()
{

	if (bPoweredOn) return;
	bPoweredOn = true;

	for (ALight* Light : CabinLights)
	{
		if (Light && Light->GetLightComponent()) Light->GetLightComponent()->SetVisibility(true);
	}

	if (RedIndicatorLight && RedIndicatorLight->GetLightComponent()) RedIndicatorLight->GetLightComponent()->SetVisibility(false);

	if (GreenIndicatorLight && GreenIndicatorLight->GetLightComponent()) GreenIndicatorLight->GetLightComponent()->SetVisibility(true);
}
