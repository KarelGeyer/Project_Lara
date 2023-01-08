// Copyright Epic Games, Inc. All Rights Reserved.

#include "LaraGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_LaraGameMode::AProject_LaraGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Main/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
