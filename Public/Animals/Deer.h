// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/AnimalBase.h"
#include "Deer.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_LARA_API ADeer : public AAnimalBase
{
	GENERATED_BODY()

public:
	ADeer();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	/* Base Speed */
	float Speed = 95.f;
};
