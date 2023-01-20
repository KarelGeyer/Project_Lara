// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Enemy/Enemy.h"
#include <Kismet/GameplayStatics.h>
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "DrawDebugHelpers.h"

AEnemy::AEnemy()
{
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::World);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageAnimation();

	if (HealthBarWidget) {
		UProgressBar* HealthBar = Cast<UProgressBar>(HealthBarWidget->GetUserWidgetObject()->GetWidgetFromName("HealthBar"));
		if (HealthBar) {
			UE_LOG(LogTemp, Warning, TEXT("HealthBar: %s"), *HealthBar->GetName());
			HealthBar->SetPercent(.5f);
		}
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetMaxMovementSpeed(MaxWalkSpeed);
	GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &AEnemy::Shoot, 1.f, true);
}

void AEnemy::SetEnemyState(EEnemyState State)
{
	EnemyState = State;
}

void AEnemy::ManageAnimation()
{
	if (EnemyState == EEnemyState::Patrol)
	{
		ManagePatrol();
	}

	if (EnemyState == EEnemyState::Chase)
	{
		ManageChase();
	}

	if (EnemyState == EEnemyState::Attack)
	{
		ManageAttack();
	}

	if (EnemyState == EEnemyState::Dead)
	{
		ManageDead();
	}
}

void AEnemy::SetStateValues(float AnimSpeed, float AnimState, bool bIsAttacking, bool bIsDead)
{
	MovementAnimationSpeed = AnimSpeed;
	MovementAnimationState = AnimState;
	IsAttacking = bIsAttacking;
	IsDead = bIsDead;
}

void AEnemy::ManagePatrol()
{
	if (IsMoving()) {
		SetStateValues(0.5, 0);
		SetMaxMovementSpeed(MaxWalkSpeed);

		return;
	}

	if (GetWorld()->GetTimerManager().IsTimerActive(ShootTimerHandle)) {
		GetWorld()->GetTimerManager().PauseTimer(ShootTimerHandle);
	}

	SetStateValues();

	return;
}

void AEnemy::ManageChase()
{
	SetStateValues(1.f);
	SetMaxMovementSpeed(MaxRunSpeed);

	if (GetWorld()->GetTimerManager().IsTimerActive(ShootTimerHandle)) {
		GetWorld()->GetTimerManager().PauseTimer(ShootTimerHandle);
	}

	return;
}

void AEnemy::ManageAttack()
{
	SetStateValues(0.f, 1.f, true);

	if (GetWorld()->GetTimerManager().IsTimerPaused(ShootTimerHandle)) {
		GetWorld()->GetTimerManager().UnPauseTimer(ShootTimerHandle);
	}

	return;
}

void AEnemy::ManageDead()
{
	SetStateValues(0.f, 0.f, false, true);

	if (GetWorld()->GetTimerManager().IsTimerActive(ShootTimerHandle)) {
		GetWorld()->GetTimerManager().ClearTimer(ShootTimerHandle);
	}

	return;
}

void AEnemy::Shoot()
{
	FHitResult Hit;

	AController* EnemyController = GetController();

	if (EnemyController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	EnemyController->GetActorEyesViewPoint(Location, Rotation);
	FVector ShotDirection = Rotation.Vector();

	FVector End = Location + (ShotDirection * MaxShootingRange);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());

	FVector RandomizedLocation = FVector(Location.X, Location.Y + FMath::RandRange(0, 30), Location.Z + FMath::RandRange(0, 30));

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, RandomizedLocation, End, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor == nullptr)
		{
			return;
		}

		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, EnemyController, this);
	}
}
