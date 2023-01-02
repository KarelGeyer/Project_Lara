// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/Wolf.h"

AWolf::AWolf()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWolf::BeginPlay()
{
	Super::BeginPlay();

	SetMovementSpeed(Speed);
}
