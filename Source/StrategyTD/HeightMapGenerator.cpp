// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Math/Color.h"
#include "HeightMapGenerator.h"

HeightMapGenerator::HeightMapGenerator()
{
	regions = new TerrainType[2];
	regions[0].name = "Water";
	regions[0].height = 0.4;
	regions[0].color = FColor::Blue;

	regions[1].name = "Landscape";
	regions[1].height = 1;
	regions[1].color = FColor(86, 152, 23, 255);
}

float* HeightMapGenerator::GenerateNoiseMap(uint32 mapWidth, uint32 mapHeight, float scale, float persistance, float lacunarity, uint32 octaves)
{
	float iterX = 1 / float(mapWidth);
	float iterY = 1 / float(mapHeight);

	float minValue = 0.f;
	float maxValue = 0.f;
	float maxCur = 0.f;
	float minCur = 0.f;
	float tempMax = 0.f;
	float tempMin = 0.f;

	noisePerlinValues = new float[mapWidth * mapHeight];

	if (iterX != 0 && iterY != 0)
	{
		for (uint32 y = 0; y < mapHeight; y++)
		{
			for (uint32 x = 0; x < mapWidth; x++)
			{
				float amplitude = 1;
				float frequency = 1;
				float noiseHeight = 0;
				int32 CurrentPointIndex = ((y * mapWidth) + x);
				for (uint32 i = 0; i < octaves; i++) {

					float sampleX = (float(x) / mapWidth * (scale * frequency));
					float sampleY = (float(y) / mapHeight * (scale * frequency));
					FVector2D sampleValues = FVector2D(sampleX, sampleY);
					float perlinValue = (FMath::PerlinNoise2D(sampleValues));
					noiseHeight += perlinValue * amplitude; //* amplitude
					amplitude *= persistance;
					frequency *= lacunarity;
				}
				noisePerlinValues[CurrentPointIndex] = noiseHeight;
			}
		}
		for (uint32 y = 0; y < mapHeight; y++)
		{
			for (uint32 x = 0; x < mapWidth; x++)
			{
				int32 CurrentPointIndex = ((y * mapWidth) + x);
				if (noisePerlinValues[CurrentPointIndex] > maxValue)
				{
					maxValue = noisePerlinValues[CurrentPointIndex];
				}
			}
			for (uint32 x = 0; x < mapWidth; x++)
			{
				uint32 CurrentPointIndex = ((y * mapWidth) + x);
				if (noisePerlinValues[CurrentPointIndex] < minValue)
				{
					minValue = noisePerlinValues[CurrentPointIndex];
				}
			}
		}

		for (uint32 y = 0; y < mapHeight; y++)
		{
			for (uint32 x = 0; x < mapWidth; x++)
			{
				int32 CurrentPointIndex = ((y * mapWidth) + x);
				noisePerlinValues[CurrentPointIndex] = UKismetMathLibrary::NormalizeToRange(noisePerlinValues[CurrentPointIndex], minValue, maxValue);
			}
		}

	}
	return noisePerlinValues;
}

void HeightMapGenerator::GenerateColorMap(uint32 mapWidth, uint32 mapHeight)
{
	colorMap = new FColor[mapWidth * mapHeight];
	for (uint32 y = 0; y < mapHeight; y++)
	{
		for (uint32 x = 0; x < mapWidth; x++)
		{
			int32 CurrentPointIndex = ((y * mapWidth) + x);
			float currentHeight = noisePerlinValues[CurrentPointIndex];

			for (uint32 i = 0; i < 2; i++)
			{
				if (currentHeight <= regions[i].height)
				{
					colorMap[(y * mapWidth) + x] = regions[i].color;
					break;
				}
			}
		}
	}
}


