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
    float* GenerateNoiseMap(uint32 mapWidth, uint32 mapHeight, float scale, float persistance, float lacunarity, uint32 octaves);
    void GenerateColorMap(uint32 mapWidth, uint32 mapHeight);
    
};
