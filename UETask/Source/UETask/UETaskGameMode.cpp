// Copyright Epic Games, Inc. All Rights Reserved.

#include "UETaskGameMode.h"
#include "UETaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUETaskGameMode::AUETaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
