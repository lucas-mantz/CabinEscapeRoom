// Fill out your copyright notice in the Description page of Project Settings.

#include "LockBoxWidget.h"

#include "CombinationLockbox.h"
#include "CabinEscapeRoomPlayerController.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

#include "Kismet/GameplayStatics.h"

void ULockBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Digit1Button)
	{
		Digit1Button->OnClicked.AddDynamic(this, &ULockBoxWidget::OnDigit1Clicked);

		Digit1Button->OnHovered.AddDynamic(this, &ULockBoxWidget::OnDigit1Hovered);

		Digit1Button->OnUnhovered.AddDynamic(this, &ULockBoxWidget::OnDigit1Unhovered);
	}

	if (Digit2Button)
	{
		Digit2Button->OnClicked.AddDynamic(this, &ULockBoxWidget::OnDigit2Clicked);

		Digit2Button->OnHovered.AddDynamic(this, &ULockBoxWidget::OnDigit2Hovered);

		Digit2Button->OnUnhovered.AddDynamic(this, &ULockBoxWidget::OnDigit2Unhovered);
	}

	if (Digit3Button)
	{
		Digit3Button->OnClicked.AddDynamic(this, &ULockBoxWidget::OnDigit3Clicked);

		Digit3Button->OnHovered.AddDynamic(this, &ULockBoxWidget::OnDigit3Hovered);

		Digit3Button->OnUnhovered.AddDynamic(this, &ULockBoxWidget::OnDigit3Unhovered);
	}

	if (Digit4Button)
	{
		Digit4Button->OnClicked.AddDynamic(this, &ULockBoxWidget::OnDigit4Clicked);

		Digit4Button->OnHovered.AddDynamic(this, &ULockBoxWidget::OnDigit4Hovered);

		Digit4Button->OnUnhovered.AddDynamic(this, &ULockBoxWidget::OnDigit4Unhovered);
	}

	if (SubmitButton)
	{
		SubmitButton->OnClicked.AddDynamic(this, &ULockBoxWidget::OnSubmitClicked);

		SubmitButton->OnHovered.AddDynamic(this, &ULockBoxWidget::OnSubmitHovered);

		SubmitButton->OnUnhovered.AddDynamic(this, &ULockBoxWidget::OnSubmitUnhovered);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &ULockBoxWidget::OnCloseClicked);

		CloseButton->OnHovered.AddDynamic(this, &ULockBoxWidget::OnCloseHovered);

		CloseButton->OnUnhovered.AddDynamic(this, &ULockBoxWidget::OnCloseUnhovered);
	}

	HideGlow(Digit1Glow);
	HideGlow(Digit2Glow);
	HideGlow(Digit3Glow);
	HideGlow(Digit4Glow);
	HideGlow(SubmitGlow);
	HideGlow(CloseGlow);
}

void ULockBoxWidget::SetLockBox(ACombinationLockBox* LockBox)
{
	CurrentLockBox = LockBox;

	RefreshDigits();
}

void ULockBoxWidget::RefreshDigits()
{
	if (!CurrentLockBox) return;

	if (Digit1Text) Digit1Text->SetText(FText::AsNumber(CurrentLockBox->GetDigit(0)));

	if (Digit2Text) Digit2Text->SetText(FText::AsNumber(CurrentLockBox->GetDigit(1)));

	if (Digit3Text) Digit3Text->SetText(FText::AsNumber(CurrentLockBox->GetDigit(2)));

	if (Digit4Text) Digit4Text->SetText(FText::AsNumber(CurrentLockBox->GetDigit(3)));
}

void ULockBoxWidget::OnDigit1Clicked()
{
	PlayClickSound();

	if (!CurrentLockBox) return;

	CurrentLockBox->IncrementDigit(0);
	RefreshDigits();
}

void ULockBoxWidget::OnDigit2Clicked()
{
	PlayClickSound();

	if (!CurrentLockBox) return;

	CurrentLockBox->IncrementDigit(1);
	RefreshDigits();
}

void ULockBoxWidget::OnDigit3Clicked()
{
	PlayClickSound();

	if (!CurrentLockBox) return;

	CurrentLockBox->IncrementDigit(2);
	RefreshDigits();
}

void ULockBoxWidget::OnDigit4Clicked()
{
	PlayClickSound();

	if (!CurrentLockBox) return;

	CurrentLockBox->IncrementDigit(3);
	RefreshDigits();
}

void ULockBoxWidget::OnSubmitClicked()
{
	PlayClickSound();

	if (!CurrentLockBox) return;

	CurrentLockBox->SubmitCode();

	if (CurrentLockBox->IsSolved())
	{
		ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(GetOwningPlayer());

		if (Controller) Controller->HideLockBox();
	}
}

void ULockBoxWidget::OnCloseClicked()
{
	PlayClickSound();

	ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(GetOwningPlayer());

	if (Controller) Controller->HideLockBox();
}

void ULockBoxWidget::ShowGlow(UBorder* Glow)
{
	if (Glow) Glow->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void ULockBoxWidget::HideGlow(UBorder* Glow)
{
	if (Glow) Glow->SetVisibility(ESlateVisibility::Hidden);
}

void ULockBoxWidget::PlayHoverSound()
{
	if (HoverSound) UGameplayStatics::PlaySound2D(this, HoverSound);
}

void ULockBoxWidget::PlayClickSound()
{
	if (ClickSound) UGameplayStatics::PlaySound2D(this, ClickSound);
}

void ULockBoxWidget::OnDigit1Hovered()
{
	ShowGlow(Digit1Glow);
	PlayHoverSound();
}

void ULockBoxWidget::OnDigit1Unhovered()
{
	HideGlow(Digit1Glow);
}

void ULockBoxWidget::OnDigit2Hovered()
{
	ShowGlow(Digit2Glow);
	PlayHoverSound();
}

void ULockBoxWidget::OnDigit2Unhovered()
{
	HideGlow(Digit2Glow);
}

void ULockBoxWidget::OnDigit3Hovered()
{
	ShowGlow(Digit3Glow);
	PlayHoverSound();
}

void ULockBoxWidget::OnDigit3Unhovered()
{
	HideGlow(Digit3Glow);
}

void ULockBoxWidget::OnDigit4Hovered()
{
	ShowGlow(Digit4Glow);
	PlayHoverSound();
}

void ULockBoxWidget::OnDigit4Unhovered()
{
	HideGlow(Digit4Glow);
}

void ULockBoxWidget::OnSubmitHovered()
{
	ShowGlow(SubmitGlow);
	PlayHoverSound();
}

void ULockBoxWidget::OnSubmitUnhovered()
{
	HideGlow(SubmitGlow);
}

void ULockBoxWidget::OnCloseHovered()
{
	ShowGlow(CloseGlow);
	PlayHoverSound();
}

void ULockBoxWidget::OnCloseUnhovered()
{
	HideGlow(CloseGlow);
}