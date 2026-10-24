// Copyright Epic Games, Inc. All Rights Reserved.

#include "CabinEscapeRoomPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "CabinEscapeRoomCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "InteractionPromptWidget.h"
#include "InventoryBarWidget.h"
#include "InventoryComponent.h"
#include "NoteReaderWidget.h"
#include "LockBoxWidget.h"
#include "CombinationLockBox.h"
#include "StartMenuWidget.h"
#include "EndMenuWidget.h"
#include "StopwatchWidget.h"

ACabinEscapeRoomPlayerController::ACabinEscapeRoomPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ACabinEscapeRoomCameraManager::StaticClass();
}

void ACabinEscapeRoomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (IsLocalPlayerController() && ShouldUseTouchControls())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);
		}
	}

	if (InteractionPromptWidgetClass)
	{
		InteractionPromptWidget = CreateWidget<UInteractionPromptWidget>(this, InteractionPromptWidgetClass);

		if (InteractionPromptWidget)
		{
			InteractionPromptWidget->AddToViewport();
			InteractionPromptWidget->HidePrompt();
		}
	}

	if (InventoryBarWidgetClass)
	{
		InventoryBarWidget = CreateWidget<UInventoryBarWidget>(this, InventoryBarWidgetClass);
		if (InventoryBarWidget) InventoryBarWidget->AddToViewport();
	}

	APawn* PlayerPawn = GetPawn();

	if (PlayerPawn)
	{
		UInventoryComponent* Inventory = PlayerPawn->FindComponentByClass<UInventoryComponent>();

		if (Inventory)
		{
			Inventory->OnInventoryChanged.AddDynamic(this, &ACabinEscapeRoomPlayerController::RefreshInventoryUI);
			RefreshInventoryUI();
		}
	}

	if (StartMenuWidgetClass)
	{
		StartMenuWidget = CreateWidget<UStartMenuWidget>(this, StartMenuWidgetClass);

		if (StartMenuWidget)
		{
			StartMenuWidget->AddToViewport();

			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);

			bShowMouseCursor = true;

			SetIgnoreMoveInput(true);
			SetIgnoreLookInput(true);
		}
	}
}

void ACabinEscapeRoomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool ACabinEscapeRoomPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void ACabinEscapeRoomPlayerController::ShowInteractionPrompt(const FText& Text)
{

	if (InteractionPromptWidget) InteractionPromptWidget->ShowPrompt(Text);
}

void ACabinEscapeRoomPlayerController::HideInteractionPrompt()
{

	if (InteractionPromptWidget) InteractionPromptWidget->HidePrompt();
}

void ACabinEscapeRoomPlayerController::RefreshInventoryUI()
{
	if (!InventoryBarWidget) return;

	APawn* PlayerPawn = GetPawn();

	if (!PlayerPawn) return;

	UInventoryComponent* Inventory = PlayerPawn->FindComponentByClass<UInventoryComponent>();

	if (!Inventory) return;

	InventoryBarWidget->RefreshInventory(Inventory->GetItems());
}

void ACabinEscapeRoomPlayerController::ShowNote(TSubclassOf<UNoteReaderWidget> NoteWidgetClass)
{
	if (!NoteWidgetClass) return;

	if (NoteReaderWidget)
	{
		NoteReaderWidget->RemoveFromParent();
		NoteReaderWidget = nullptr;
	}

	NoteReaderWidget = CreateWidget<UNoteReaderWidget>(this, NoteWidgetClass);

	if (!NoteReaderWidget) return;

	NoteReaderWidget->AddToViewport();

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);

	bShowMouseCursor = true;

	SetIgnoreMoveInput(true);
	SetIgnoreLookInput(true);
}

void ACabinEscapeRoomPlayerController::HideNote()
{
	if (NoteReaderWidget)
	{
		NoteReaderWidget->RemoveFromParent();
		NoteReaderWidget = nullptr;
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	bShowMouseCursor = false;

	SetIgnoreMoveInput(false);
	SetIgnoreLookInput(false);
}

void ACabinEscapeRoomPlayerController::ShowLockBox(ACombinationLockBox* LockBox)
{
	if (!LockBox || !LockBoxWidgetClass) return;

	if (!LockBoxWidget) LockBoxWidget = CreateWidget<ULockBoxWidget>(this, LockBoxWidgetClass);

	if (!LockBoxWidget) return;

	LockBoxWidget->SetLockBox(LockBox);

	if (!LockBoxWidget->IsInViewport()) LockBoxWidget->AddToViewport();

	FInputModeUIOnly InputMode;

	InputMode.SetWidgetToFocus(LockBoxWidget->TakeWidget());

	SetInputMode(InputMode);

	bShowMouseCursor = true;
}

void ACabinEscapeRoomPlayerController::HideLockBox()
{
	if (LockBoxWidget) LockBoxWidget->RemoveFromParent();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	bShowMouseCursor = false;
}

void ACabinEscapeRoomPlayerController::StartGame()
{
	if (StartMenuWidget)
	{
		StartMenuWidget->RemoveFromParent();
		StartMenuWidget = nullptr;
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	bShowMouseCursor = false;

	SetIgnoreMoveInput(false);
	SetIgnoreLookInput(false);

	GameStartTime = GetWorld()->GetTimeSeconds();

	FinalGameTime = 0.0f;

	bGameTimerRunning = true;

	if (StopwatchWidgetClass)
	{
		StopwatchWidget = CreateWidget<UStopwatchWidget>(this, StopwatchWidgetClass);

		if (StopwatchWidget) StopwatchWidget->AddToViewport();
	}
}

float ACabinEscapeRoomPlayerController::GetElapsedGameTime() const
{
	if (bGameTimerRunning && GetWorld()) return GetWorld()->GetTimeSeconds() - GameStartTime;

	return FinalGameTime;
}

float ACabinEscapeRoomPlayerController::StopGameTimer()
{
	if (!bGameTimerRunning) return FinalGameTime;

	FinalGameTime = GetElapsedGameTime();

	bGameTimerRunning = false;

	return FinalGameTime;
}

void ACabinEscapeRoomPlayerController::EndGame()
{
	const float FinalTime = StopGameTimer();

	SetIgnoreMoveInput(true);
	SetIgnoreLookInput(true);

	if (StopwatchWidget)
	{
		StopwatchWidget->RemoveFromParent();
		StopwatchWidget = nullptr;
	}

	if (!EndMenuWidgetClass) return;

	EndMenuWidget = CreateWidget<UEndMenuWidget>(this, EndMenuWidgetClass);

	if (!EndMenuWidget) return;

	EndMenuWidget->SetFinalTime(FinalTime);

	EndMenuWidget->AddToViewport();

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);

	bShowMouseCursor = true;
}
