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
	SelectedActors = HudPtr->FoundActors;
}

void AMainCameraPlayerController::MoveReleased()
{
	if (SelectedActors.Num() > 0)
	{
		for (int32 i = 0; i < SelectedActors.Num(); i++)
		{
			FVector MoveLocation;
			//UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetInstigatorController(), MoveLocation); // AMYACTOR MÅSTE GÖRAS OM TILL EN PAWN!!!!
			//UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
		}
	}
}

void AMainCameraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AMainCameraPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &AMainCameraPlayerController::SelectionReleased);
	InputComponent->BindAction("RightMouseClick", IE_Released, this, &AMainCameraPlayerController::MoveReleased);

}