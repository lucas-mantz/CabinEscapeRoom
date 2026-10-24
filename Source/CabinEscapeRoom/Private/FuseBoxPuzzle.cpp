// Fill out your copyright notice in the Description page of Project Settings.

#include "FuseBoxPuzzle.h"

AFuseBoxPuzzle::AFuseBoxPuzzle()
{

	PrimaryActorTick.bCanEverTick = true;
}

void AFuseBoxPuzzle::ToggleCircuit(EFuseCircuit Circuit)
{
	if (bSolved) return;

	switch (Circuit)
	{
	case EFuseCircuit::Lights:
		bLightsOn = !bLightsOn;
		break;

	case EFuseCircuit::Bedroom:
		bBedroomOn = !bBedroomOn;
		break;

	case EFuseCircuit::Heater:
		bHeaterOn = !bHeaterOn;
		break;

	case EFuseCircuit::Security:
		bSecurityOn = !bSecurityOn;
		break;

	default:
		return;
	}

	CheckSolution();
}

bool AFuseBoxPuzzle::IsCircuitOn(EFuseCircuit Circuit) const
{

	switch (Circuit)
	{
	case EFuseCircuit::Lights:
		return bLightsOn;

	case EFuseCircuit::Bedroom:
		return bBedroomOn;

	case EFuseCircuit::Heater:
		return bHeaterOn;

	case EFuseCircuit::Security:
		return bSecurityOn;

	default:
		return false;
	}
}

void AFuseBoxPuzzle::CheckSolution()
{

	const bool bCorrect = bLightsOn == bLightsShouldBeOn && bBedroomOn == bBedroomShouldBeOn && bHeaterOn == bHeaterShouldBeOn && bSecurityOn == bSecurityShouldBeOn;

	if (bCorrect) CompletePuzzle();
}
