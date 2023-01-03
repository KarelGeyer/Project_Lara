// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalBase.generated.h"

UCLASS()
class PROJECT_LARA_API AAnimalBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimalBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Location to patroll around */
	FVector InitialPosition;
	/* Location to patroll around */
	int32 BaseState;

	/* Location to patroll around */
	UPROPERTY(EditInstanceOnly, Category = "Location")
		FVector PatrolLocation;
	/* Represents a movement speed depending on the state */
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		float MovementAnimationSpeed = 0.f;
	/*Represents and idle state*/
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		float IdleAnimationState = 0.f;

	/*return whether the pawn is currently moving*/
	bool IsMoving();

protected:
	virtual void BeginPlay() override;
	/* Movement Component */
	UCharacterMovementComponent* MovementComponent;

	/*Sets the max speed for the pawn*/
	virtual void SetMovementSpeed(float Speed);
	/*Manages the animations*/
	virtual void ManageAnim();
	/*Sets the idle animation state*/
	virtual void SetIdleAnimationState();
	/*Sets All the timers*/
	virtual void SetTimers(int IdleStateChangeRate = 2.f);
};
