// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndMenuWidget.generated.h"

class UButton;
class UBorder;
class UTextBlock;
class USoundBase;

UCLASS()
class CABINESCAPEROOM_API UEndMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetFinalTime(float FinalTime);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PlayAgainButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> PlayAgainGlow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> QuitGlow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> FinalTimeText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> HoverSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> ClickSound;

	UFUNCTION()
	void OnPlayAgainClicked();

	UFUNCTION()
	void OnQuitClicked();

	UFUNCTION()
	void OnPlayAgainHovered();

	UFUNCTION()
	void OnPlayAgainUnhovered();

	UFUNCTION()
	void OnQuitHovered();

	UFUNCTION()
	void OnQuitUnhovered();
};
