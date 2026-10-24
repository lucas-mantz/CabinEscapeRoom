// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventoryBarWidget.generated.h"

class UImage;

UCLASS()
class CABINESCAPEROOM_API UInventoryBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshInventory(const TArray<FInventoryItem>& Items);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Slot1Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Slot2Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Slot3Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Slot4Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Slot5Icon;
};
