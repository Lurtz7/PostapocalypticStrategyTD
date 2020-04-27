// Fill out your copyright notice in the Description page of Project Settings.


#include "Worldmap.h"

// Sets default values
AWorldmap::AWorldmap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcedualMesh"));
	TextureGeneratorPtr = new TextureGenerator();
	HeightmapPtr = new HeightMapGenerator();

	height = HeightmapPtr->GenerateNoiseMap(256, 256, 15.f, 0.5f,2.5f,5);
	CreateMesh(256, 256);
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

AWorldmap::MeshData::MeshData(uint32 meshWidth, uint32 meshHeight)
{
	normals.Init(FVector(0.0f, 0.0f, 1.0f), meshWidth * meshHeight);
	tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), meshWidth * meshHeight);
	vertexColors.Init(FLinearColor(0.f, 0.f, 0.f), meshWidth * meshHeight);
}

void AWorldmap::MeshData::AddTriangle(uint32 a, uint32 b, uint32 c)
{
	Triangles.EmplaceAt(triangleIndex, a);
	Triangles.EmplaceAt(triangleIndex + 1, b);
	Triangles.EmplaceAt(triangleIndex + 2, c);
	triangleIndex += 3;
}

void AWorldmap::CreateMesh(uint32 mapWidth, uint32 mapHeight)
{

	float scaleXY = 100;
	float scaleZ = 700;
	
	meshData = new MeshData(mapWidth, mapHeight);
	int vertexIndex = 0;
	float topLeftX = (mapWidth - 1) / -2.f; //FUNGERAR INTE ?
	float topLeftZ = (mapHeight - 1) / 2.f;
	for (uint32 y = 0; y < mapHeight; y++)
	{
		for (uint32 x = 0; x < mapWidth; x++)
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

	UE_LOG(LogTemp, Warning, TEXT("Size Vertex: %d"), meshData->Vertices.Num());
	UE_LOG(LogTemp, Warning, TEXT("Size Triangles: %d"), meshData->Triangles.Num());
	UE_LOG(LogTemp, Warning, TEXT("Size normals: %d"), meshData->normals.Num());
	UE_LOG(LogTemp, Warning, TEXT("Size UVS: %d"), meshData->UVS.Num());
	UE_LOG(LogTemp, Warning, TEXT("Size TANG: %d"), meshData->tangents.Num());
	UE_LOG(LogTemp, Warning, TEXT("Size VertexColor: %d"), meshData->vertexColors.Num());

	/*for (int i = 0; i < meshData->Triangles.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT(" Vertex: %d "), meshData->Triangles[i]);
	}*/
	/*for (int i = 0; i < meshData->Vertices.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT(" Vertex: %f , %f , %f"), meshData->Vertices[i].X, meshData->Vertices[i].Y, meshData->Vertices[i].Z);
	}*/

	Mesh->CreateMeshSection_LinearColor(0, meshData->Vertices, meshData->Triangles, meshData->normals, meshData->UVS, meshData->vertexColors, meshData->tangents, true);
}
