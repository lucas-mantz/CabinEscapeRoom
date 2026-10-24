// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryBarWidget.h"
#include "Components/Image.h"

void UInventoryBarWidget::RefreshInventory(const TArray<FInventoryItem>& Items)
{
	UImage* Slots[] = {Slot1Icon, Slot2Icon, Slot3Icon, Slot4Icon, Slot5Icon};

	for (int32 i = 0; i < 5; i++)
	{
		if (!Slots[i]) continue;
		if (Items.IsValidIndex(i) && Items[i].Icon)
		{
			Slots[i]->SetBrushFromTexture(Items[i].Icon);
			Slots[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
			Slots[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}
