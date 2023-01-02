// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/AI/WolfAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


AWolfAIController::AWolfAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWolfAIController::BeginPlay()
{
	Super::BeginPlay();
}
