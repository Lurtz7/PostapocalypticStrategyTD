// Fill out your copyright notice in the Description page of Project Settings.


#include "Citadell.h"

// Sets default values
ACitadell::ACitadell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACitadell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACitadell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACitadell::SetSelected() 
{
	//Toggle UI
	isSelectionActivatedCitadell = true;
}
void ACitadell::SetDeselected() 
{
	//Toggle UI
	isSelectionActivatedCitadell = false;
}
