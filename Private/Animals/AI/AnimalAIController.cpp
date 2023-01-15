// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/AI/AnimalAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>
#include "Animals/AnimalBase.h"
#include "NavigationSystem.h"
#include "NavigationSystemTypes.h"

AAnimalAIController::AAnimalAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAnimalAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InitializeAI();

}

void AAnimalAIController::BeginPlay()
{
	Super::BeginPlay();

	GetBasePawn();
}

void AAnimalAIController::InitializeAI()
{
	if (Animal && Animal->GetDistanceFromPlayer() < 10000.f) {
		if (AIBehavior) {

			RunBehaviorTree(AIBehavior);

			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLocation"), Animal->PatrolLocation);
			GetBlackboardComponent()->SetValueAsVector(TEXT("InitialPosition"), Animal->GetActorLocation());
			GetBlackboardComponent()->SetValueAsInt(TEXT("State"), Animal->BaseState);
		}
	}

	if (Animal && Animal->GetDistanceFromPlayer() > 10000.f) {
		StopMovement();
	}
}

void AAnimalAIController::GetBasePawn()
{
	Animal = Cast<AAnimalBase>(GetPawn());
}

