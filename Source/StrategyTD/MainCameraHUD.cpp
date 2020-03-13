// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraPlayerController.h"
#include "MainCameraHUD.h"



void AMainCameraHUD::DrawHUD()
{

	if (bStartSelecting)
	{
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(1, 0, 0, 0.15), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);

	}
	
}

FVector2D AMainCameraHUD::GetMousePos2D()
{
	float PosX;
	float PosY;

	GetOwningPlayerController()->GetMousePosition(PosX, PosY);

	return FVector2D(PosX, PosY);


}
