// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/AnimalBase.h"
#include "Pig.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_LARA_API APig : public AAnimalBase
{
	GENERATED_BODY()

public:
	APig();
protected:
	virtual void BeginPlay() override;

private:
	/* Base Speed */
	float Speed = 95.f;
};
