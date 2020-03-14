// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MainCameraHUD.h"
#include "GameFramework/PlayerController.h"
#include "MainCameraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYTD_API AMainCameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainCameraPlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	AMainCameraHUD* HudPtr;
	class AMainCameraMovement* ValueHolder;

	

protected:
	void SelectionPressed();
	void SelectionReleased();
	void MoveReleased();
	TArray<AMyActor*>SelectedActors;
	
 
	
};
