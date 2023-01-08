// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_Base.generated.h"

class APlayerCharacter;

UENUM(Category = "Location")
enum ELocationType
{
	InitialLoc,
	PatrolLoc,
	PlayerLoc,
};

UCLASS()
class PROJECT_LARA_API ANPC_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC_Base();

public:
	virtual void Tick(float DeltaTime) override;

	/*Controls the speed animation depending on the movement speed*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float MovementAnimationSpeed = 0.f;

	/*Controls wheter the movement is in atack mode or not*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float MovementAnimationState = 1.f;

	/*Initial Location the pawn starts the game at*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Location")
		FVector InitialLocation;

	/*Location to patrol to from its initial position*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Location")
		FVector PatrolLocation;

	/* Player class*/
	UPROPERTY(BlueprintReadOnly, Category = "Player")
		APlayerCharacter* PlayerCharacter;

	/*Get Distance from player*/
	UFUNCTION(Category = "Player")
		float GetDistanceFromPlayer();

	/*Get Distance from Initial position set on begin play*/
	UFUNCTION(Category = "Movement")
		float GetDistanceFromLocation(ELocationType LocationType);

	/*Sets Maximum movement speed*/
	UFUNCTION(Category = "Movement")
		void SetMaxMovementSpeed(float Speed);

protected:
	virtual void BeginPlay() override;

	/*Is Pawn Dead*/
	UPROPERTY(BlueprintReadOnly, Category = "State")
		bool IsDead = false;

	/*Checks wheter the pawn is currently moving*/
	bool IsMoving();

private:
	/* Maximum movement speed*/
	float MaxSpeed = 100.0f;

	/*Manges the rotation of the pawn when walking*/
	void ManageRotation();

	/*Manages Animation states*/
	virtual void ManageAnimation();

};
