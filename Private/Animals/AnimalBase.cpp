#include "Animals/AnimalBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

void AAnimalBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

bool AAnimalBase::IsMoving()
{
	FVector Velocity = GetVelocity();
	double Movement = Velocity.SizeSquared();

	return Movement > 0;
}