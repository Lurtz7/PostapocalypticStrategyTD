// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldMapDummySPawner.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/UObjectGlobals.h"
#include "Worldmap.h"

// Sets default values
AWorldmap::AWorldmap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcedualMesh");
	TextureGeneratorPtr = new TextureGenerator();
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> BarFillObj(TEXT("/Game/Assets/Terrain/M_Landscape_GrassRock_Inst"));
	//worldMapMaterial = BarFillObj.Object;

	//WaterMesh = CreateDefaultSubobject<UStaticMeshComponent>("WaterMesh");
	HeightmapPtr = new HeightMapGenerator();
}

// Called when the game starts or when spawned
void AWorldmap::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWorldmap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AWorldmap::MeshData::MeshData(int32 meshWidth, int32 meshHeight)
{
	//normals.Init(FVector(0.0f, 0.0f, 1.0f), meshWidth*meshHeight);
	//tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), meshWidth * meshHeight);
	vertexColors.Init(FLinearColor(0.f, 0.f, 0.f), meshWidth * meshHeight);
}

void AWorldmap::MeshData::AddTriangle(int32 a, int32 b, int32 c)
{
	Triangles.EmplaceAt(triangleIndex, a);
	Triangles.EmplaceAt(triangleIndex + 1, b);
	Triangles.EmplaceAt(triangleIndex + 2, c);
	triangleIndex += 3;
}

void AWorldmap::CreateMesh(int32 mapWidth, int32 mapHeight)
{

	float scaleXY = 1.f;
	float scaleZ =1.f;
	float maxValue = 0;
	int32 focusValue = 0;

	meshData = new MeshData(mapWidth, mapHeight);
	int vertexIndex = 0;

	int verteXIndexWater = 0;
	int vertexIndexTerrain = 0;

	float topLeftX = (mapWidth - 1) / -2.f; //FUNGERAR INTE ?
	float topLeftZ = (mapHeight - 1) / 2.f;
	float additionalHeight = 0;

	for (int32 y = 0; y < mapHeight; y++)
	{
		for (int32 x = 0; x < mapWidth; x++)
		{
			int32 CurrentPointIndex = ((y * mapWidth) + x);
			if (*(height + CurrentPointIndex) > maxValue)
			{
				maxValue = *(height + CurrentPointIndex);
				focusValue = CurrentPointIndex;
			}
		}
	}

	// Percentage 30%
	//for (int32 y = 0; y < mapHeight; y++)
	//{
	//	for (int32 x = 0; x < mapWidth; x++)
	//	{
	//		int32 CurrentPointIndex = ((y * mapWidth) + x);
	//		if (CurrentPointIndex  <  focusValue - mapWidth && CurrentPointIndex < focusValue - mapWidth - 1 && CurrentPointIndex > focusValue - mapWidth + 1)
	//		{
	//			if (CurrentPointIndex < focusValue - mapWidth - 1 && CurrentPointIndex < focusValue - 1 && CurrentPointIndex > focusValue + mapWidth -1)
	//			{
	//				if (CurrentPointIndex < focusValue + mapWidth + 1 && CurrentPointIndex < focusValue + 1 && CurrentPointIndex > focusValue + mapWidth + 1)
	//				{
	//					if (CurrentPointIndex < focusValue + mapWidth -1 && CurrentPointIndex < focusValue + mapWidth && CurrentPointIndex > focusValue + mapWidth + 1)
	//					{
	//						// Kolla så att punkt inte ligger på utanför område
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	for (int32 y = 0; y < mapHeight; y++)
	{
		for (int32 x = 0; x < mapWidth; x++)
		{
			int32 CurrentPointIndex = ((y * mapWidth) + x);
			if (x == (mapWidth / 2) - 1)
			{
				for(int32 top = mapWidth / 8 - ((mapWidth / 8) / 2) ; top < (mapWidth/8 ) / 2; top++)
				{
					*(height + CurrentPointIndex  + top) = *(height + CurrentPointIndex) * 100;
				}
			}
		}
	}



	for (int32 y = 0; y < mapHeight; y++)
	{
		for (int32 x = 0; x < mapWidth; x++)
		{
			int32 CurrentPointIndex = ((y * mapWidth) + x);
			meshData->Vertices.Add(FVector((topLeftX + x) * scaleXY, (topLeftZ - y) * scaleXY, *(height  + CurrentPointIndex) * (scaleZ) ));
			meshData->UVS.Add(FVector2D((x / float(mapWidth)) * scaleXY, (y / float(mapHeight)) * scaleXY));
			if (x < mapWidth - 1 && y < mapHeight - 1)
			{
				meshData->AddTriangle(vertexIndex, vertexIndex + mapWidth + 1, vertexIndex + mapWidth);
				meshData->AddTriangle(vertexIndex + mapWidth + 1, vertexIndex, vertexIndex + 1);
			}
			vertexIndex++;
		}
	}
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(meshData->Vertices, meshData->Triangles, meshData->UVS, meshData->normals, meshData->tangents);

	Mesh->CreateMeshSection_LinearColor(0, meshData->Vertices, meshData->Triangles, meshData->normals, meshData->UVS, meshData->vertexColors, meshData->tangents, true);
	//Mesh->SetMaterial(0, worldMapMaterial);
}

void AWorldmap::createWorld(int32 mapHeight, int32 mapWidth, float noiseScale, float persistace, float lucanarity, int32 octaves)
{
	UE_LOG(LogTemp, Warning, TEXT(" Vertex: %d"), mapWidth);
	UE_LOG(LogTemp, Warning, TEXT(" Vertex: %d"), mapHeight);

	UE_LOG(LogTemp, Warning, TEXT(" Vertex: %f"), noiseScale);
	UE_LOG(LogTemp, Warning, TEXT(" Vertex: %f"), persistace);
	UE_LOG(LogTemp, Warning, TEXT(" Vertex: %f"), lucanarity);

	UE_LOG(LogTemp, Warning, TEXT(" Vertex: %d"), octaves);


	height = HeightmapPtr->GenerateNoiseMap(mapWidth, mapHeight, noiseScale,persistace, lucanarity, octaves);
	CreateMesh(mapWidth, mapHeight);
}

void AWorldmap::CreateWater(float planeHeight, int32 mapHeight, int32 mapWidth)
{

}