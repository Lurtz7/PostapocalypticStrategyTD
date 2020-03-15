// Fill out your copyright notice in the Description page of Project Settings.


#include "AIType1.h"

// Sets default values
AAIType1::AAIType1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIType1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIType1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIType1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void  AAIType1::SetSelected()
{
	//Set visibility true
}
void AAIType1::SetDeselected()
{
	//Set off

}
