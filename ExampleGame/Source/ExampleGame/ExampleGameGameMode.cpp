// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ExampleGame.h"
#include "ExampleGameGameMode.h"
#include "ExampleGameCharacter.h"

AExampleGameGameMode::AExampleGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
