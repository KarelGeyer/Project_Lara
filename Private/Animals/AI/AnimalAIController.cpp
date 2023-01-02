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
}

void AAnimalAIController::BeginPlay()
{
	Super::BeginPlay();

	GetBasePawn();
	InitializeAI();
}

void AAnimalAIController::InitializeAI()
{
	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);

		if (Animal) {
			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLocation"), Animal->PatrolLocation);
			GetBlackboardComponent()->SetValueAsVector(TEXT("InitialPosition"), Animal->GetActorLocation());
			GetBlackboardComponent()->SetValueAsInt(TEXT("State"), Animal->BaseState);
		}

	}
}

void AAnimalAIController::GetBasePawn()
{
	Animal = Cast<AAnimalBase>(GetPawn());
}

