// Fill out your copyright notice in the Description page of Project Settings.

#include "StopwatchWidget.h"

#include "CabinEscapeRoomPlayerController.h"
#include "Components/TextBlock.h"

void UStopwatchWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ACabinEscapeRoomPlayerController* Controller = Cast<ACabinEscapeRoomPlayerController>(GetOwningPlayer());

	if (!Controller || !StopwatchText) return;

	const float ElapsedTime = Controller->GetElapsedGameTime();

	const int32 TotalSeconds = FMath::FloorToInt(ElapsedTime);

	const int32 Minutes = TotalSeconds / 60;

	const int32 Seconds = TotalSeconds % 60;

	const FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	StopwatchText->SetText(FText::FromString(TimeString));
}
