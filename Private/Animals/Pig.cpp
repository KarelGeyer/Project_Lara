// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/Pig.h"

APig::APig()
{
}

void APig::BeginPlay()
{
	Super::BeginPlay();

	SetMovementSpeed(Speed);
	SetTimers(2.f);
}
