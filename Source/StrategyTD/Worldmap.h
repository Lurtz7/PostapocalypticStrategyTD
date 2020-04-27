// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TextureGenerator.h"
#include "HeightMapGenerator.h"
#include "CoreMinimal.h"
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
		MeshData(uint32 meshWidth, uint32 meshHeight); // Constructor för MeshData struct
		void AddTriangle(uint32 a, uint32 b, uint32 c); //Adderar alla triangelpunkter. 
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
	void CreateMesh(uint32 mapWidth, uint32 mapHeight);

	//POINTERS
	TerrainType* regions;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UProceduralMeshComponent* Mesh;

	MeshData* meshData;

	TextureGenerator* TextureGeneratorPtr;

	HeightMapGenerator* HeightmapPtr;

	float* height;


	//OBJECTS

public:	
	// Sets default values for this actor's properties
	AWorldmap();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
