// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "ReadableNote.generated.h"

class UStaticMeshComponent;
class UNoteReaderWidget;
class USoundBase;

UCLASS()
class CABINESCAPEROOM_API AReadableNote
	: public AActor,
	  public IInteractableInterface
{
	GENERATED_BODY()

public:
	AReadableNote();

	virtual void Interact_Implementation(AActor* Interactor) override;

	virtual FText GetInteractionText_Implementation()
		const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Note")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Note")
	TObjectPtr<UStaticMeshComponent> NoteMesh;

	// Which note UI this world note opens.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Note")
	TSubclassOf<UNoteReaderWidget> NoteWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> InteractionSound;

	// Lets different notes have different prompts.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Note")
	FText InteractionText = FText::FromString(TEXT("[E] Read Note"));
};