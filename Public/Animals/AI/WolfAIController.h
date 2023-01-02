// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/AI/AnimalAIController.h"
#include "WolfAIController.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_LARA_API AWolfAIController : public AAnimalAIController
{
	GENERATED_BODY()

public:
	AWolfAIController();

protected:
	virtual void BeginPlay() override;
};
