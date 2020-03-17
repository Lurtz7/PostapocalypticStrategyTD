// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"


AMainCameraPlayerController::AMainCameraPlayerController()
{
	AutoReceiveInput = EAutoReceiveInput::Player0;
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
	SelectedActorsCitadell = HudPtr->FoundActorsCitadell;
}

FVector AMainCameraPlayerController::GetRandomPos() const
{
	//  My random vector implementation goes here
	FVector MyRandomVector;

	return MyRandomVector;
}


void AMainCameraPlayerController::MoveReleased()
{
	if (SelectedActors.Num() > 0)
	{
		FVector Destination = GetRandomPos();
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MoveLocation);
		for (int32 i = 0; i < SelectedActors.Num(); i++)
		{
			FHitResult Hita;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hita);
			FVector MoveLocationC = Hita.Location + FVector(i/2*200, i % 2 * 200,0);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocationC);

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