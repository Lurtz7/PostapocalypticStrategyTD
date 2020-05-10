// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TextureGenerator.h"
#include "HeightMapGenerator.h"
#include "Engine/Engine.h"
#include "KismetProceduralMeshLibrary.h"
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Worldmap.generated.h"

UCLASS()
class STRATEGYTD_API AWorldmap : public AActor
{
	GENERATED_BODY()


private:
	 //STRUCTS
	struct MeshData {
		UPROPERTY(VisibleAnywhere)
			TArray<FVector> Vertices;
		UPROPERTY(VisibleAnywhere)
			TArray<int32> Triangles;
		UPROPERTY(VisibleAnywhere)
			TArray<FVector2D> UVS;
		UPROPERTY(VisibleAnywhere)
			TArray<FVector> normals;
		UPROPERTY(VisibleAnywhere)
			TArray<FLinearColor> vertexColors;
		UPROPERTY(VisibleAnywhere)
			TArray<FProcMeshTangent> tangents;

		int32 triangleIndex = 0;
		bool bCreateCollision = true;
		MeshData(int32 meshWidth, int32 meshHeight); // Constructor för MeshData struct

		void AddTriangle(int32 a, int32 b, int32 c); //Adderar alla triangelpunkter. 
	};

	struct TerrainType {

		UPROPERTY(VisibleAnywhere)
		FString name;
		UPROPERTY(VisibleAnywhere)
		float height;
		UPROPERTY(VisibleAnywhere)
		FColor color;
	};

	//FUNCTIONS
	void CreateMesh(int32 mapWidth, int32 mapHeight);
	void CreateWater(float planeHeight, int32 mapHeight, int32 mapWidth);
	
	//POINTERS
	TerrainType* regions;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* WaterMesh;

	UPROPERTY(VisibleAnywhere)
		UMaterialInterface* worldMapMaterial;


	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* Mesh;

	MeshData* meshData;


	TextureGenerator* TextureGeneratorPtr;

	HeightMapGenerator* HeightmapPtr;

	class AWorldMapDummySPawner* retainValues;
	

	float* height;


	//OBJECTS

public:	
	// Sets default values for this actor's properties
	AWorldmap();

	UFUNCTION(BlueprintCallable)
	void createWorld(int32 mapHeight, int32 mapWidth, float noiseScale, float persistace, float lucanarity, int32 octaves);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
