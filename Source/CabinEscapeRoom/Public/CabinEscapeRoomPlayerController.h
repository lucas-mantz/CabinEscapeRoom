// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CabinEscapeRoomPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class UInteractionPromptWidget;
class UInventoryBarWidget;
class UInventoryComponent;
class UNoteReaderWidget;
class ULockBoxWidget;
class ACombinationLockBox;
class UStartMenuWidget;
class UEndMenuWidget;
class UStopwatchWidget;

/**
 * Simple first person Player Controller
 * Manages the input mapping context.
 * Overrides the Player Camera Manager class.
 */
UCLASS(abstract, config = "Game")
class CABINESCAPEROOM_API ACabinEscapeRoomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Constructor */
	ACabinEscapeRoomPlayerController();

	void ShowInteractionPrompt(const FText& Text);

	void HideInteractionPrompt();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowNote(TSubclassOf<UNoteReaderWidget> NoteWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideNote();

	void ShowLockBox(ACombinationLockBox* LockBox);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideLockBox();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintPure, Category = "Game")
	float GetElapsedGameTime() const;

protected:
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInteractionPromptWidget> InteractionPromptWidgetClass;

	UPROPERTY()
	UInteractionPromptWidget* InteractionPromptWidget;

	void UpdateInteractionPrompt();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInventoryBarWidget> InventoryBarWidgetClass;

	UPROPERTY()
	TObjectPtr<UInventoryBarWidget> InventoryBarWidget;

	UFUNCTION()
	void RefreshInventoryUI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UNoteReaderWidget> NoteReaderWidgetClass;

	UPROPERTY()
	TObjectPtr<UNoteReaderWidget> NoteReaderWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ULockBoxWidget> LockBoxWidgetClass;

	UPROPERTY()
	TObjectPtr<ULockBoxWidget> LockBoxWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UStartMenuWidget> StartMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UStartMenuWidget> StartMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEndMenuWidget> EndMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UEndMenuWidget> EndMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UStopwatchWidget> StopwatchWidgetClass;

	UPROPERTY()
	TObjectPtr<UStopwatchWidget> StopwatchWidget;

private:
	float GameStartTime = 0.0f;

	float FinalGameTime = 0.0f;

	bool bGameTimerRunning = false;

	float StopGameTimer();
};
