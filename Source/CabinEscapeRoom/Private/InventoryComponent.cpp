// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventoryComponent::AddItem(const FInventoryItem& Item)
{
	if (Item.ItemId.IsNone()) return false;
	if (Items.Num() >= MaxSlots) return false;
	if (HasItem(Item.ItemId)) return false;

	Items.Add(Item);

	OnInventoryChanged.Broadcast();

	return true;
}

bool UInventoryComponent::HasItem(FName ItemId) const
{
	return Items.ContainsByPredicate([ItemId](const FInventoryItem& Item)
									 { return Item.ItemId == ItemId; });
}

bool UInventoryComponent::RemoveItem(FName ItemId)
{
	const int32 ItemIndex = Items.IndexOfByPredicate([ItemId](const FInventoryItem& Item)
													 { return Item.ItemId == ItemId; });

	if (ItemIndex == INDEX_NONE) return false;

	Items.RemoveAt(ItemIndex);

	OnInventoryChanged.Broadcast();

	return true;
}
