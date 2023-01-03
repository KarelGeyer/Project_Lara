// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/Deer.h"

ADeer::ADeer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADeer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADeer::BeginPlay()
{
	Super::BeginPlay();

	SetMovementSpeed(Speed);
	SetTimers(FMath::RandRange(7.f, 15.f));
}
