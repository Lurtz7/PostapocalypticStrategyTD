// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TestUtanPluginGameMode.h"
#include "TestUtanPluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestUtanPluginGameMode::ATestUtanPluginGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
