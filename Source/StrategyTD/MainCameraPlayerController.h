// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MainCameraMovement.h"
#include "GameFramework/Pawn.h"
#include "MainCameraHUD.h"
#include "Citadell.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
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
	const FVector* MoveLocation;
	FVector GetRandomPos() const;
	void MoveReleased();

protected:
	void SelectionPressed();
	void SelectionReleased();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ÁIItems")
		TArray<AAIEnemyCharacter*>SelectedActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ÁIItems")
		TArray<ACitadell*>SelectedActorsCitadell;
	
 
	
};
