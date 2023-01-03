// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/Fox.h"

AFox::AFox()
{
}

void AFox::BeginPlay()
{
	Super::BeginPlay();

	SetMovementSpeed(Speed);
}
