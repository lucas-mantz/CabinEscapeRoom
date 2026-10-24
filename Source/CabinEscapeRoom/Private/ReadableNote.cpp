// Fill out your copyright notice in the Description page of Project Settings.

#include "ReadableNote.h"

#include "CabinEscapeRoomPlayerController.h"
#include "NoteReaderWidget.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

AReadableNote::AReadableNote()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = Root;

	NoteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NoteMesh"));

	NoteMesh->SetupAttachment(Root);
}

void AReadableNote::Interact_Implementation(AActor* Interactor)
{
	if (!Interactor || !NoteWidgetClass) return;

	APawn* Pawn = Cast<APawn>(Interactor);

	if (!Pawn) return;

	ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(Pawn->GetController());

	if (!Controller) return;

	Controller->ShowNote(NoteWidgetClass);

	if (InteractionSound) UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
}

FText AReadableNote::GetInteractionText_Implementation() const
{
	return InteractionText;
}