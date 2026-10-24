// Fill out your copyright notice in the Description page of Project Settings.

#include "EndMenuWidget.h"

#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UEndMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayAgainButton)
	{
		PlayAgainButton->OnClicked.AddDynamic(this, &UEndMenuWidget::OnPlayAgainClicked);

		PlayAgainButton->OnHovered.AddDynamic(this, &UEndMenuWidget::OnPlayAgainHovered);

		PlayAgainButton->OnUnhovered.AddDynamic(this, &UEndMenuWidget::OnPlayAgainUnhovered);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UEndMenuWidget::OnQuitClicked);

		QuitButton->OnHovered.AddDynamic(this, &UEndMenuWidget::OnQuitHovered);

		QuitButton->OnUnhovered.AddDynamic(this, &UEndMenuWidget::OnQuitUnhovered);
	}

	if (PlayAgainGlow) PlayAgainGlow->SetVisibility(ESlateVisibility::Hidden);

	if (QuitGlow) QuitGlow->SetVisibility(ESlateVisibility::Hidden);
}

void UEndMenuWidget::SetFinalTime(float FinalTime)
{
	if (!FinalTimeText) return;

	const int32 TotalSeconds = FMath::FloorToInt(FinalTime);

	const int32 Minutes = TotalSeconds / 60;

	const int32 Seconds = TotalSeconds % 60;

	const FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	FinalTimeText->SetText(FText::FromString(TimeString));
}

void UEndMenuWidget::OnPlayAgainClicked()
{
	if (ClickSound) UGameplayStatics::PlaySound2D(this, ClickSound);

	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);

	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}

void UEndMenuWidget::OnQuitClicked()
{
	if (ClickSound) UGameplayStatics::PlaySound2D(this, ClickSound);

	APlayerController* Controller = GetOwningPlayer();

	UKismetSystemLibrary::QuitGame(this, Controller, EQuitPreference::Quit, false);
}

void UEndMenuWidget::OnPlayAgainHovered()
{
	if (PlayAgainGlow) PlayAgainGlow->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (HoverSound) UGameplayStatics::PlaySound2D(this, HoverSound);
}

void UEndMenuWidget::OnPlayAgainUnhovered()
{
	if (PlayAgainGlow) PlayAgainGlow->SetVisibility(ESlateVisibility::Hidden);
}

void UEndMenuWidget::OnQuitHovered()
{
	if (QuitGlow) QuitGlow->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (HoverSound) UGameplayStatics::PlaySound2D(this, HoverSound);
}

void UEndMenuWidget::OnQuitUnhovered()
{
	if (QuitGlow) QuitGlow->SetVisibility(ESlateVisibility::Hidden);
}