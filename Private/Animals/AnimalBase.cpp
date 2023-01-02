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

	FTimerHandle IdleTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(IdleTimerHandle, this, &AAnimalBase::SetIdleAnimationState, 2.f, true);
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
		UE_LOG(LogTemp, Warning, TEXT("Moving"));
		MovementAnimationSpeed = 0.5f;

		return;
	}

	MovementAnimationSpeed = 0.f;
}

void AAnimalBase::SetIdleAnimationState()
{
	if (!IsMoving()) {
		IdleAnimationState = FMath::RandRange(0.f, 1.f);
	}
}

bool AAnimalBase::IsMoving()
{
	FVector Velocity = GetVelocity();
	double Movement = Velocity.SizeSquared();

	return Movement > 0;
}