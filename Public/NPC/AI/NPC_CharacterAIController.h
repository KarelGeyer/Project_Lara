// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_CharacterAIController.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_LARA_API ANPC_CharacterAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANPC_CharacterAIController();

	virtual void Tick(float DeltaTime) override;
};
