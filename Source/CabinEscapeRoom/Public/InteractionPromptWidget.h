// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPromptWidget.generated.h"

class UTextBlock;

UCLASS()
class CABINESCAPEROOM_API UInteractionPromptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowPrompt(const FText& InteractionText);

	void HidePrompt();

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionTextBlock;
};
