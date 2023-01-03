// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/AI/AnimalAIController.h"
#include "DeerAIController.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_LARA_API ADeerAIController : public AAnimalAIController
{
	GENERATED_BODY()

public:
	ADeerAIController();

protected:
	virtual void BeginPlay() override;
};
