// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraPlayerController.h"
#include "MainCameraMovement.h"


AMainCameraPlayerController::AMainCameraPlayerController()
{
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMainCameraPlayerController::BeginPlay()
{
	HudPtr = Cast<AMainCameraHUD>(GetHUD());
	ValueHolder = Cast<AMainCameraMovement>(GetPawn());
}


void AMainCameraPlayerController::SelectionPressed()
{
	HudPtr->InitialPoint = HudPtr->GetMousePos2D();
	HudPtr->bStartSelecting = true;
	ValueHolder->IsLeftMouseButtonDown = true;

}

void AMainCameraPlayerController::SelectionReleased()
{
	HudPtr->bStartSelecting = false;
	ValueHolder->IsLeftMouseButtonDown = false;
}

void AMainCameraPlayerController::MoveReleased()
{
	
}

void AMainCameraPlayerController::Constrains()
{

}



void AMainCameraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AMainCameraPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &AMainCameraPlayerController::SelectionReleased);
	InputComponent->BindAction("RightMouseClick", IE_Released, this, &AMainCameraPlayerController::MoveReleased);
	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AMainCameraPlayerController::Constrains);

}