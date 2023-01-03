// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/AnimalBase.h"
#include "Fox.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_LARA_API AFox : public AAnimalBase
{
	GENERATED_BODY()

public:
	AFox();
protected:
	virtual void BeginPlay() override;

private:
	/* Base Speed */
	float Speed = 50.f;
};
