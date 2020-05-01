// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldMapDummySPawner.h"

// Sets default values
AWorldMapDummySPawner::AWorldMapDummySPawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
}

void AWorldMapDummySPawner::spawnWorldMap(int32 mapHeight, int32 mapWidth, float noiseScale, float persistace, float lucanarity, int32 octaves)
{
	NmapHeight = mapHeight;
	NmapWidth = mapWidth;
	NnoiseScale = noiseScale;
	Npersistance = persistace;
	Nlacunarity = lucanarity;
	Noctaves = octaves;


	//UE_LOG(LogTemp, Warning, TEXT(" Vertex: %f"), Npersistance);
	//UE_LOG(LogTemp, Warning, TEXT(" Vertex: %d"), NmapHeight);
}

// Called when the game starts or when spawned
void AWorldMapDummySPawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldMapDummySPawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

