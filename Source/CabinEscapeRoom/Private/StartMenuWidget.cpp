// Fill out your copyright notice in the Description page of Project Settings.

#include "StartMenuWidget.h"
#include "CabinEscapeRoomPlayerController.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnStartClicked);
		StartButton->OnHovered.AddDynamic(this, &UStartMenuWidget::OnStartHovered);
		StartButton->OnUnhovered.AddDynamic(this, &UStartMenuWidget::OnStartUnhovered);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnQuitClicked);
		QuitButton->OnHovered.AddDynamic(this, &UStartMenuWidget::OnQuitHovered);
		QuitButton->OnUnhovered.AddDynamic(this, &UStartMenuWidget::OnQuitUnhovered);
	}

	if (StartGlow) StartGlow->SetVisibility(ESlateVisibility::Hidden);

	if (QuitGlow) QuitGlow->SetVisibility(ESlateVisibility::Hidden);
}

void UStartMenuWidget::OnStartClicked()
{
	ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(GetOwningPlayer());

	if (Controller) Controller->StartGame();

	if (ClickSound) UGameplayStatics::PlaySound2D(this, ClickSound);
}

void UStartMenuWidget::OnQuitClicked()
{
	if (ClickSound) UGameplayStatics::PlaySound2D(this, ClickSound);

	ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(GetOwningPlayer());

	UKismetSystemLibrary::QuitGame(this, Controller, EQuitPreference::Quit, false);
}

void UStartMenuWidget::OnStartHovered()
{
	if (StartGlow) StartGlow->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (HoverSound) UGameplayStatics::PlaySound2D(this, HoverSound);
}

void UStartMenuWidget::OnStartUnhovered()
{
	if (StartGlow) StartGlow->SetVisibility(ESlateVisibility::Hidden);
}

void UStartMenuWidget::OnQuitHovered()
{
	if (QuitGlow) QuitGlow->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (HoverSound) UGameplayStatics::PlaySound2D(this, HoverSound);
}

void UStartMenuWidget::OnQuitUnhovered()
{

	if (QuitGlow) QuitGlow->SetVisibility(ESlateVisibility::Hidden);
}
