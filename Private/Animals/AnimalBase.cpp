#include "Animals/AnimalBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

AAnimalBase::AAnimalBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = GetCharacterMovement();
	InitialPosition = GetActorLocation();
	BaseState = 1;
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageAnim();
	SetVisibility();
}

void AAnimalBase::SetMovementSpeed(float Speed)
{
	if (MovementComponent) {
		MovementComponent->MaxWalkSpeed = Speed;
	}
}

void AAnimalBase::ManageAnim()
{
	if (IsMoving()) {
		MovementAnimationSpeed = 0.5f;

		return;
	}

	MovementAnimationSpeed = 0.f;
}

void AAnimalBase::SetIdleAnimationState()
{
	IdleAnimationState = FMath::RandRange(0.f, 1.f);
}

void AAnimalBase::SetTimers(int IdleStateChangeRate)
{
	FTimerHandle IdleTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(IdleTimerHandle, this, &AAnimalBase::SetIdleAnimationState, IdleStateChangeRate, true);
}

void AAnimalBase::SetVisibility()
{
	RootComponent->GetChildComponent(1)->SetVisibility(GetDistanceFromPlayer() > 10000.f);
}

bool AAnimalBase::IsMoving()
{
	FVector Velocity = GetVelocity();
	double Movement = Velocity.SizeSquared();

	return Movement > 0;
}

void AAnimalBase::SetPatrolLocation(FVector Location)
{
	PatrolLocation = Location;
}

float AAnimalBase::GetDistanceFromPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector NewPlayerLocation = PlayerPawn->GetActorLocation();
	FVector Location = GetActorLocation();

	return FVector::Dist(Location, NewPlayerLocation);
}
