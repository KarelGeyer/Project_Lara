// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_LaraGameMode.h"
#include "Project_LaraCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_LaraGameMode::AProject_LaraGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
