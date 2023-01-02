// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/AnimalBase.h"
#include "Wolf.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_LARA_API AWolf : public AAnimalBase
{
	GENERATED_BODY()

public:
	AWolf();
protected:
	virtual void BeginPlay() override;

private:
	/* Base Speed */
	float Speed = 80.f;
};
