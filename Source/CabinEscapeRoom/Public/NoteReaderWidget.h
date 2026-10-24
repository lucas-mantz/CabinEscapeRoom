// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteReaderWidget.generated.h"

class UButton;
class UBorder;
class USoundBase;

UCLASS()
class CABINESCAPEROOM_API UNoteReaderWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> CloseGlow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> HoverSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> ClickSound;

	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION()
	void OnCloseHovered();

	UFUNCTION()
	void OnCloseUnhovered();

private:
	void ShowCloseGlow();
	void HideCloseGlow();

	void PlayHoverSound();
	void PlayClickSound();
};