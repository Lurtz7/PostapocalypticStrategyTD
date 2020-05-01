// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STRATEGYTD_API HeightMapGenerator
{

private:
   

    //STRUCTS
    struct TerrainType {
        FString name;
        float height;
        FColor color;
    };

    // POINTERS

    float* noisePerlinValues;
    FColor* colorMap;
    TerrainType* regions;


public:
	HeightMapGenerator();
    float* GenerateNoiseMap(int32 mapWidth, int32 mapHeight, float scale, float persistance, float lacunarity, int32 octaves);
    void GenerateColorMap(int32 mapWidth, int32 mapHeight);
    
};
