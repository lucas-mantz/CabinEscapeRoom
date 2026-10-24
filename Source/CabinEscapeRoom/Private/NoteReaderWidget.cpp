// Fill out your copyright notice in the Description page of Project Settings.

#include "NoteReaderWidget.h"

#include "CabinEscapeRoomPlayerController.h"

#include "Components/Button.h"
#include "Components/Border.h"

#include "Kismet/GameplayStatics.h"

void UNoteReaderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UNoteReaderWidget::OnCloseClicked);

		CloseButton->OnHovered.AddDynamic(this, &UNoteReaderWidget::OnCloseHovered);

		CloseButton->OnUnhovered.AddDynamic(this, &UNoteReaderWidget::OnCloseUnhovered);
	}

	HideCloseGlow();
}

void UNoteReaderWidget::OnCloseClicked()
{
	PlayClickSound();

	ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(GetOwningPlayer());

	if (Controller) Controller->HideNote();
}

void UNoteReaderWidget::OnCloseHovered()
{
	ShowCloseGlow();
	PlayHoverSound();
}

void UNoteReaderWidget::OnCloseUnhovered()
{
	HideCloseGlow();
}

void UNoteReaderWidget::ShowCloseGlow()
{
	if (CloseGlow) CloseGlow->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UNoteReaderWidget::HideCloseGlow()
{
	if (CloseGlow) CloseGlow->SetVisibility(ESlateVisibility::Hidden);
}

void UNoteReaderWidget::PlayHoverSound()
{
	if (HoverSound) UGameplayStatics::PlaySound2D(this, HoverSound);
}

void UNoteReaderWidget::PlayClickSound()
{
	if (ClickSound) UGameplayStatics::PlaySound2D(this, ClickSound);
}
