// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "AIEnemyCharacter.h"
#include "Citadell.h"
#include "MainCameraHUD.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYTD_API AMainCameraHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;

	FVector2D InitialPoint;
	FVector2D CurrentPoint;

	FVector2D GetMousePos2D();

	bool bStartSelecting = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pawn")
		TArray<AAIEnemyCharacter*>FoundActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pawn")
		TArray<ACitadell*>FoundActorsCitadell;
	
};
