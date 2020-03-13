// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraMovement.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainCameraPlayerController.h"
#include "Engine/Engine.h"

// Sets default values
AMainCameraMovement::AMainCameraMovement()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraSpringArmComponent");
	CameraArm->SetupAttachment(StaticMesh);
	CameraArm->TargetArmLength = 500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetupAttachment(CameraArm);

	SetRootComponent(StaticMesh);

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

}

// Called when the game starts or when spawned
void AMainCameraMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCameraMovement::MoveForward(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * Amount);
}

void AMainCameraMovement::MoveRight(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector() * Amount);
}

void AMainCameraMovement::Turn(float Amount)
{
	AddControllerYawInput(Amount);
}

void AMainCameraMovement::LookUp(float Amount)
{	
	AddControllerPitchInput(Amount);

}

// Called every frame
void AMainCameraMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Called to bind functionality to input
void AMainCameraMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCameraMovement::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCameraMovement::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMainCameraMovement::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCameraMovement::LookUp);
}

