// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldMapDummySPawner.generated.h"

UCLASS()
class STRATEGYTD_API AWorldMapDummySPawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldMapDummySPawner();

	class AWorldmap* worldMapPtr;

	int32 NmapHeight = 0;
	int32 NmapWidth = 0;
	float NnoiseScale = 0.0f;
	float Npersistance = 0.0f;
	float Nlacunarity = 0.0f;
	int32 Noctaves = 0.0f;


	UFUNCTION(BlueprintCallable)
	void spawnWorldMap(int32 mapHeight, int32 mapWidth, float noiseScale, float persistace, float lucanarity, int32 octaves);

	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
