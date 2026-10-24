// Fill out your copyright notice in the Description page of Project Settings.

#include "BookshelfPuzzle.h"
#include "PullableBook.h"
#include "HingedInteractable.h"
#include "InventoryPickup.h"

ABookshelfPuzzle::ABookshelfPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABookshelfPuzzle::RegisterBook(APullableBook* Book)
{
	if (!Book) return;

	Books.AddUnique(Book);
}

void ABookshelfPuzzle::TryBook(APullableBook* Book)
{
	if (!Book)
	{
		return;
	}

	if (bSolved)
	{
		return;
	}

	const int32 BookOrder = Book->GetCorrectOrder();

	if (BookOrder == CurrentStep)
	{
		Book->SetPulled(true);

		CurrentStep++;

		if (CurrentStep >= RequiredBookCount)
		{
			CompletePuzzle();

			if (SecretCompartment) SecretCompartment->Open();

			if (RewardPickup) RewardPickup->SetPickupEnabled(true);
		}

		return;
	}

	PlayIncorrectSound();
	ResetPuzzle();
}

void ABookshelfPuzzle::ResetPuzzle()
{

	CurrentStep = 0;

	for (APullableBook* Book : Books)
	{
		if (Book) Book->SetPulled(false);
	}
}
