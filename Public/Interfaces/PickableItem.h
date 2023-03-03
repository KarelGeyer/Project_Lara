// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickableItem.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickableItem : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class PROJECT_LARA_API IPickableItem
{
	GENERATED_BODY()

public:
	FString ItemName;

	/* Returns the Item Name*/
	virtual FString GetItemName();
};
