// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC_Base.h"
#include <Kismet/GameplayStatics.h>
#include <Project_Lara/PlayerCharacter.h>
#include <Kismet/KismetMathLibrary.h>
#include "GameFramework/CharacterMovementComponent.h"

ANPC_Base::ANPC_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

void ANPC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageRotation();
}

float ANPC_Base::GetDistanceFromPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector NewPlayerLocation = PlayerPawn->GetActorLocation();
	FVector Location = GetActorLocation();

	return FVector::Dist(Location, NewPlayerLocation);
}

float ANPC_Base::GetDistanceFromLocation(ELocationType LocationType)
{
	if (LocationType == ELocationType::InitialLoc)
	{
		return FVector::Dist(GetActorLocation(), InitialLocation);
	}

	if (LocationType == ELocationType::PatrolLoc)
	{
		return FVector::Dist(GetActorLocation(), PatrolLocation);
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector NewPlayerLocation = PlayerPawn->GetActorLocation();
	FVector Location = GetActorLocation();

	return FVector::Dist(Location, NewPlayerLocation);
}

bool ANPC_Base::IsMoving()
{
	FVector Velocity = GetVelocity();
	double Movement = Velocity.SizeSquared();

	return Movement > 0;
}

void ANPC_Base::SetMaxMovementSpeed(float Speed)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent) {
		MovementComponent->MaxWalkSpeed = Speed;
	}
}

void ANPC_Base::ManageRotation()
{
	if (IsMoving()) {
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + GetVelocity());
		SetActorRotation(NewRotation);
	}
}

void ANPC_Base::ManageAnimation()
{
}
