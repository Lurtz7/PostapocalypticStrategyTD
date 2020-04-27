// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STRATEGYTD_API TextureGenerator
{
public:
	TextureGenerator();
	void CreateProceduralTexture(int32 textureHeight, int32 textureWidth, FColor colorMap[], float noisePerlinValues[], bool isItNoiseMap);


private:
	//POINTERS
	UPROPERTY()
	UPackage* Package;

	//Variables
	FString PackageName;
	FString BaseTextureName;

	bool drawMode = true;
};
