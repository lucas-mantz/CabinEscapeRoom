// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleBase.h"
#include "FuseBoxPuzzle.generated.h"

UENUM(BlueprintType)
enum class EFuseCircuit : uint8
{
	Lights UMETA(DisplayName = "Lights"),
	Bedroom UMETA(DisplayName = "Bedroom"),
	Heater UMETA(DisplayName = "Heater"),
	Security UMETA(DisplayName = "Security"),
};

UCLASS()
class CABINESCAPEROOM_API AFuseBoxPuzzle : public APuzzleBase
{
	GENERATED_BODY()

public:
	AFuseBoxPuzzle();

	UFUNCTION(BlueprintCallable, Category = "Fuse Box")
	void ToggleCircuit(EFuseCircuit Circuit);

	UFUNCTION(BlueprintPure, Category = "Fuse box")
	bool IsCircuitOn(EFuseCircuit Circuit) const;

protected:
	void CheckSolution();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fuse Box|State")
	bool bLightsOn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fuse Box|State")
	bool bBedroomOn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fuse Box|State")
	bool bHeaterOn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fuse Box|State")
	bool bSecurityOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FuseBox|Solution")
	bool bLightsShouldBeOn = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FuseBox|Solution")
	bool bBedroomShouldBeOn = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FuseBox|Solution")
	bool bHeaterShouldBeOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FuseBox|Solution")
	bool bSecurityShouldBeOn = true;
};