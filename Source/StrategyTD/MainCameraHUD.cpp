// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraHUD.h"
#include "MainCameraPlayerController.h"




void AMainCameraHUD::DrawHUD()
{

	if (bStartSelecting)
	{
		if (FoundActors.Num() > 0)
		{
			for (int32 i = 0; i < FoundActors.Num(); i++)
			{
				FoundActors[i]->SetDeselected();
			}
		}
		if (FoundActorsCitadell.Num() > 0)
		{
			for (int32 i = 0; i < FoundActorsCitadell.Num(); i++)
			{
				FoundActorsCitadell[i]->SetDeselected();
			}
		}
		FoundActors.Empty();
		FoundActorsCitadell.Empty();

		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(1, 0, 0, 0.15), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
		GetActorsInSelectionRectangle<AAIEnemyCharacter>(InitialPoint, CurrentPoint, FoundActors, false, false);
		GetActorsInSelectionRectangle<ACitadell>(InitialPoint, CurrentPoint, FoundActorsCitadell, false, false);

		
		if (FoundActors.Num() > 0)
		{
			for (int32 i = 0; i < FoundActors.Num(); i++)
			{
				FoundActors[i]->SetSelected();
			}
		}
		if (FoundActorsCitadell.Num() > 0)
		{
			for (int32 i = 0; i < FoundActorsCitadell.Num(); i++)
			{
				FoundActorsCitadell[i]->SetSelected();
			}
		}
	}
	
}

FVector2D AMainCameraHUD::GetMousePos2D()
{
	float PosX;
	float PosY;

	GetOwningPlayerController()->GetMousePosition(PosX, PosY);

	return FVector2D(PosX, PosY);


}
