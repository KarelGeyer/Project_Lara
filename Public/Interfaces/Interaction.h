// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteraction : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_LARA_API IInteraction
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Runs when Actor enters the player's interaction zone
	virtual void OnInteractZoneEnter();

	// Runs when Actor leaves the player's interaction zone
	virtual void OnInteractZoneLeave();

	// Runs when the player interacts with the Actor
	virtual void OnInteract();
};
