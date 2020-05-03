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
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcedualMesh"));

	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> BarFillObj(TEXT("/Game/Material/WorldmapMaterial/m_WorldmapMaterial_Inst"));
	//worldMapMaterial = BarFillObj.Object;
	TextureGeneratorPtr = new TextureGenerator();
	HeightmapPtr = new HeightMapGenerator();

	regions = new TerrainType[2];
	regions[0].name = "Water";
	regions[0].height = 0.4;
	regions[0].color = FColor::Blue;

	regions[1].name = "Landscape";
	regions[1].height = 1;
	regions[1].color = FColor(86, 152, 23, 255);
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
	normals.Init(FVector(0.0f, 0.0f, 1.0f), meshWidth*meshHeight);
	tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), meshWidth * meshHeight);
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

	float scaleXY = 100.f;
	float scaleZ = 500.f;
	
	meshData = new MeshData(mapWidth, mapHeight);
	MeshDataWater = new MeshData(mapWidth, mapHeight);
	MeshDataTerrain = new MeshData(mapWidth, mapHeight);
	int vertexIndex = 0;

	int verteXIndexWater = 0;
	int vertexIndexTerrain = 0;


	float topLeftX = (mapWidth - 1) / -2.f; //FUNGERAR INTE ?
	float topLeftZ = (mapHeight - 1) / 2.f;

	for (int32 y = 0; y < mapHeight; y++)
	{
		for (int32 x = 0; x < mapWidth; x++)
		{
			int32 CurrentPointIndex = ((y * mapWidth) + x);
			meshData->Vertices.Add(FVector((topLeftX + x) * scaleXY, (topLeftZ - y) * scaleXY, *(height + CurrentPointIndex) * scaleZ ));
			meshData->UVS.Add(FVector2D((x / float(mapWidth)) * scaleXY, (y / float(mapHeight)) * scaleXY));
			if (x < mapWidth - 1 && y < mapHeight - 1)
			{
				meshData->AddTriangle(vertexIndex, vertexIndex + mapWidth + 1, vertexIndex + mapWidth);
				meshData->AddTriangle(vertexIndex + mapWidth + 1, vertexIndex, vertexIndex + 1);
			}
			vertexIndex++;
		}
	}

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
