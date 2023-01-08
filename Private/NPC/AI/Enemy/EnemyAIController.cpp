// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/Enemy/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/Enemy/Enemy.h"
#include <Kismet/GameplayStatics.h>

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageChasePlayer();
	ManagePatrol();
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	GetBasePawn();

	GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, this, &AEnemyAIController::SetPatrolDirection, 15.f, true);
}

void AEnemyAIController::GetBasePawn()
{
	EnemyCharacter = Cast<AEnemy>(GetPawn());
}

void AEnemyAIController::ManageChasePlayer()
{
	if (EnemyCharacter == nullptr) {
		return;
	}

	if (LineOfSightTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) && EnemyCharacter->GetDistanceFromPlayer() < EnemyCharacter->ChaseDistance)
	{
		GetWorld()->GetTimerManager().PauseTimer(PatrolTimerHandle);
		APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PlayerCharacter == nullptr) {
			return;
		}

		bIsPatrolling = false;
		EnemyCharacter->SetEnemyState(EEnemyState::Chase);

		SetFocus(PlayerCharacter);
		MoveTo(PlayerCharacter);

		if (EnemyCharacter->GetDistanceFromPlayer() < EnemyCharacter->AttackDistance) {
			EnemyCharacter->SetEnemyState(EEnemyState::Attack);
			StopMovement();
		}
	}
	else {
		EnemyCharacter->SetEnemyState(EEnemyState::Patrol);
		bIsPatrolling = true;
	}
}

void AEnemyAIController::ManagePatrol()
{
	if (EnemyCharacter == nullptr) {
		return;
	}

	if (bIsPatrolling) {
		if (GetWorld()->GetTimerManager().IsTimerPaused(PatrolTimerHandle)) {
			GetWorld()->GetTimerManager().UnPauseTimer(PatrolTimerHandle);
		}

		ClearFocus(2);

		if (bIsGoingTOPatrolLocation) {
			MoveTo(EnemyCharacter->PatrolLocation);
		}

		if (!bIsGoingTOPatrolLocation) {
			MoveTo(EnemyCharacter->InitialLocation);
		}
	}
}

void AEnemyAIController::SetPatrolDirection()
{
	bIsGoingTOPatrolLocation = !bIsGoingTOPatrolLocation;
}
