// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_Base.generated.h"

UCLASS()
class PROJECT_LARA_API ANPC_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC_Base();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Maximum movement speed*/
	float MaxSpeed = 100.0f;

};
