// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/NPC_CharacterAIController.h"

ANPC_CharacterAIController::ANPC_CharacterAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPC_CharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


