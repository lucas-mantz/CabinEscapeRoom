// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryPickup.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

void AInventoryPickup::BeginPlay()
{
	Super::BeginPlay();

	SetPickupEnabled(bStartsEnabled);
}

AInventoryPickup::AInventoryPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = Root;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	ItemMesh->SetupAttachment(Root);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));

	InteractionBox->SetupAttachment(Root);

	// The interaction trace should hit the box
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);

	InteractionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// We DON'T want the mesh stealing the interaction trace.
	ItemMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

void AInventoryPickup::SetPickupEnabled(bool bEnabled)
{
	bPickupEnabled = bEnabled;

	if (InteractionBox) InteractionBox->SetCollisionEnabled(bEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void AInventoryPickup::Interact_Implementation(AActor* Interactor)
{
	if (!bPickupEnabled || !Interactor) return;

	UInventoryComponent* Inventory = Interactor->FindComponentByClass<
		UInventoryComponent>();

	if (!Inventory)
	{
		if (PickupFailedSound) UGameplayStatics::PlaySoundAtLocation(this, PickupFailedSound, GetActorLocation());
		return;
	}

	if (Inventory->AddItem(ItemData))
	{
		if (PickupSound) UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		Destroy();
		return;
	}

	if (PickupFailedSound) UGameplayStatics::PlaySoundAtLocation(this, PickupFailedSound, GetActorLocation());
}

FText AInventoryPickup::GetInteractionText_Implementation() const
{
	if (!bPickupEnabled) return FText::GetEmpty();

	return FText::Format(FText::FromString(TEXT("[E] Pick up {0}")), ItemData.DisplayName);
}
