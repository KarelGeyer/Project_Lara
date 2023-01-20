// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPC_Base.h"
#include "Enemy.generated.h"

class UWidgetComponent;

/* A set of states the enemy can be in*/
UENUM(Category = "State")
enum EEnemyState {
	Patrol,
	Chase,
	Attack,
	Dead,
};

UCLASS()
class PROJECT_LARA_API AEnemy : public ANPC_Base
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	/* Distanve at which the enemy will be chasing the player */
	UPROPERTY(BlueprintReadOnly, Category = "Player")
		float ChaseDistance = 2000.f;

	/* Distanve at which the enemy will be attacking the player */
	UPROPERTY(BlueprintReadOnly, Category = "Player")
		float AttackDistance = 1300;

	/*Maximum Speed for running*/
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float MaxRunSpeed = 800.0f;

	/*Maximum Speed for walking*/
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float MaxWalkSpeed = 80.0f;

	/* Value represents whether */
	UPROPERTY(BlueprintReadOnly, Category = "State")
		bool IsAttacking = false;

	/* Distane at which the enemy will be attacking/chasing the player */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
		float Health;

	/* The range at which the enemy can shoot the player */
	UPROPERTY(BlueprintReadOnly, Category = "Attack")
		float MaxShootingRange = 1000.f;

	/* Damage to be applied on the Player or possibly other pawns */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
		float Damage;

	/*Get Distance from player*/
	UFUNCTION(Category = "State")
		void SetEnemyState(EEnemyState State);

	/* An interaction Widget component*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UWidgetComponent* HealthBarWidget;

protected:
	virtual void BeginPlay() override;

private:
	/* Distane at which the enemy will be attacking/chasing the player */
	EEnemyState EnemyState = Patrol;

	/*Timer handle to manage shooting*/
	FTimerHandle ShootTimerHandle;

	/*Manage Enemy Animations*/
	virtual void ManageAnimation() override;

	/*Set State values*/
	void SetStateValues(float AnimSpeed = 0.f, float AnimState = 1.f, bool bIsAttacking = false, bool bIsDead = false);

	/* Manage Patrol state*/
	void ManagePatrol();

	/*Manage Chase state*/
	void ManageChase();

	/*Manage Attack state*/
	void ManageAttack();

	/*Manage Dead state*/
	void ManageDead();

	/*Manage shooting*/
	void Shoot();
};
