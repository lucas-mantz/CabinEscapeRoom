// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockBoxWidget.generated.h"

class UButton;
class UTextBlock;
class UBorder;
class USoundBase;
class ACombinationLockBox;

UCLASS()
class CABINESCAPEROOM_API ULockBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetLockBox(ACombinationLockBox* LockBox);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Digit1Text;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Digit2Text;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Digit3Text;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Digit4Text;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Digit1Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Digit2Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Digit3Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Digit4Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SubmitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Digit1Glow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Digit2Glow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Digit3Glow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Digit4Glow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> SubmitGlow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> CloseGlow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> HoverSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> ClickSound;

	UFUNCTION()
	void OnDigit1Clicked();

	UFUNCTION()
	void OnDigit2Clicked();

	UFUNCTION()
	void OnDigit3Clicked();

	UFUNCTION()
	void OnDigit4Clicked();

	UFUNCTION()
	void OnSubmitClicked();

	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION()
	void OnDigit1Hovered();

	UFUNCTION()
	void OnDigit1Unhovered();

	UFUNCTION()
	void OnDigit2Hovered();

	UFUNCTION()
	void OnDigit2Unhovered();

	UFUNCTION()
	void OnDigit3Hovered();

	UFUNCTION()
	void OnDigit3Unhovered();

	UFUNCTION()
	void OnDigit4Hovered();

	UFUNCTION()
	void OnDigit4Unhovered();

	UFUNCTION()
	void OnSubmitHovered();

	UFUNCTION()
	void OnSubmitUnhovered();

	UFUNCTION()
	void OnCloseHovered();

	UFUNCTION()
	void OnCloseUnhovered();

private:
	UPROPERTY()
	TObjectPtr<ACombinationLockBox> CurrentLockBox;

	void RefreshDigits();

	void ShowGlow(UBorder* Glow);
	void HideGlow(UBorder* Glow);

	void PlayHoverSound();
	void PlayClickSound();
};
