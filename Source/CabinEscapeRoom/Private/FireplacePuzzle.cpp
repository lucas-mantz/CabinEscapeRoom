// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplacePuzzle.h"

#include "InventoryComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

#include "NiagaraComponent.h"

#include "HingedInteractable.h"
#include "Kismet/GameplayStatics.h"

AFireplacePuzzle::AFireplacePuzzle()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = Root;

	FireplaceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireplaceMesh"));

	FireplaceMesh->SetupAttachment(Root);
	FireplaceMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));

	InteractionBox->SetupAttachment(Root);

	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);

	InteractionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	PlacedFirewoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlacedFirewoodMesh"));

	PlacedFirewoodMesh->SetupAttachment(Root);

	PlacedNewspaperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlacedNewspaperMesh"));

	PlacedNewspaperMesh->SetupAttachment(Root);

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));

	FireEffect->SetupAttachment(Root);

	FireLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FireLight"));

	FireLight->SetupAttachment(Root);
}

void AFireplacePuzzle::BeginPlay()
{
	Super::BeginPlay();

	CurrentStage = EFireplaceStage::Empty;

	PlacedFirewoodMesh->SetVisibility(false);
	PlacedNewspaperMesh->SetVisibility(false);

	FireEffect->Deactivate();

	FireLight->SetVisibility(false);
}

void AFireplacePuzzle::Interact_Implementation(AActor* Interactor)
{
	if (!Interactor || bSolved) return;

	const EFireplaceStage PreviousStage = CurrentStage;

	switch (CurrentStage)
	{
	case EFireplaceStage::Empty:
		PlaceFirewood(Interactor);
		break;

	case EFireplaceStage::WoodPlaced:
		PlaceNewspaper(Interactor);
		break;

	case EFireplaceStage::TinderPlaced:
		LightFire(Interactor);
		break;

	case EFireplaceStage::Lit:
		StokeFire(Interactor);
		break;

	case EFireplaceStage::Completed:
		break;
	}

	if (CurrentStage == PreviousStage)
	{
		PlayIncorrectSound();
		return;
	}

	USoundBase* StageSound = nullptr;
	switch (PreviousStage)
	{
	case EFireplaceStage::Empty:
		StageSound = FirewoodPlacedSound;
		break;

	case EFireplaceStage::WoodPlaced:
		StageSound = NewspaperPlacedSound;
		break;

	case EFireplaceStage::TinderPlaced:
		StageSound = FireLitSound;
		break;

	case EFireplaceStage::Lit:
		StageSound = FireStokedSound;
		break;

	case EFireplaceStage::Completed:
		break;
	}

	if (StageSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			StageSound,
			GetActorLocation()
		);
	}

	if (CurrentStage == EFireplaceStage::Completed)
	{
		CompletePuzzle();

		if (LeftExitDoor) LeftExitDoor->Open();
		if (RightExitDoor) RightExitDoor->Open();
	}
}

void AFireplacePuzzle::PlaceFirewood(AActor* Interactor)
{
	UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();

	if (!Inventory) return;

	if (!Inventory->HasItem(FirewoodItemId)) return;

	Inventory->RemoveItem(FirewoodItemId);

	PlacedFirewoodMesh->SetVisibility(true);

	CurrentStage = EFireplaceStage::WoodPlaced;
}

void AFireplacePuzzle::PlaceNewspaper(AActor* Interactor)
{
	UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();

	if (!Inventory) return;

	if (!Inventory->HasItem(NewspaperItemId)) return;

	Inventory->RemoveItem(NewspaperItemId);

	PlacedNewspaperMesh->SetVisibility(true);

	CurrentStage = EFireplaceStage::TinderPlaced;
}

void AFireplacePuzzle::LightFire(AActor* Interactor)
{
	UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();

	if (!Inventory) return;

	if (!Inventory->HasItem(MatchesItemId)) return;

	Inventory->RemoveItem(MatchesItemId);

	FireEffect->Activate();
	FireLight->SetVisibility(true);

	CurrentStage = EFireplaceStage::Lit;
}

void AFireplacePuzzle::StokeFire(AActor* Interactor)
{
	UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();

	if (!Inventory) return;

	if (!Inventory->HasItem(PokerItemId)) return;

	CurrentStage = EFireplaceStage::Completed;
}

FText AFireplacePuzzle::GetInteractionText_Implementation() const
{
	switch (CurrentStage)
	{
	case EFireplaceStage::Empty:
		return FText::FromString(TEXT("[E] Place Firewood"));

	case EFireplaceStage::WoodPlaced:
		return FText::FromString(TEXT("[E] Add Newspaper"));

	case EFireplaceStage::TinderPlaced:
		return FText::FromString(TEXT("[E] Light Fire"));

	case EFireplaceStage::Lit:
		return FText::FromString(TEXT("[E] Stoke Fire"));

	case EFireplaceStage::Completed:
		return FText::GetEmpty();
	}

	return FText::GetEmpty();
}
