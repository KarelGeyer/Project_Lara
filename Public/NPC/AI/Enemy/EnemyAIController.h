// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AEnemy;

UCLASS()
class PROJECT_LARA_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:

	AEnemyAIController();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/*Behavior Tree*/
	UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBehavior;

private:
	/*Enemy Character*/
	AEnemy* EnemyCharacter;

	/*Timer for running SetPatrolDirection*/
	FTimerHandle PatrolTimerHandle;

	/*Boolean value to check whether the pawn can patrol and adjust behavior accordingly*/
	bool bIsPatrolling = true;

	/*Set in Timer Function and manipulates the direction the pawn is going heading*/
	bool bIsGoingTOPatrolLocation = true;

	/*Get Enemy Pawn*/
	void GetBasePawn();

	/*Manage behavior to chase player*/
	void ManageChasePlayer();

	/* Manage behavior to patrol around preset location*/
	void ManagePatrol();

	/*Countdown to manage timer*/
	void SetPatrolDirection();
};
