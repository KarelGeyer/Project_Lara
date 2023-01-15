// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class UBoxComponent;
class ANPC_Base;
class AAIController;
class AAnimalBase;

UCLASS()
class PROJECT_LARA_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/*A class based on which we spawn an NPC*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
		TSubclassOf<ANPC_Base> ClassToSpawn;

	/*A class based on which we spawn a controller for the NPC*/
	UPROPERTY(EditAnywhere, Category = "NPC")
		TSubclassOf<AAIController>  AIControllerClass;

	/* Target distance for spawned npc to patroll to*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "NPC")
		FVector SpawnNpcPatrolLocation;

	virtual void Tick(float DeltaTime) override;

private:
	/* A Box component*/
	UBoxComponent* BoxComponent;

	/* A Mesh component*/
	UStaticMeshComponent* MeshComponent;

	/* Spanwed AI Controller object in the world*/
	AAIController* AIController;

	/* Spanwed Npc object in the world*/
	ANPC_Base* NPCToSpawn;

	/* Represents whether NPC is already spawned or not*/
	bool bIsNPCSpawned = false;

	/* Distance at which NPCs will be spawned*/
	float RenderDistance = 10000.f;

	/* Spawn NPC when player is in range*/
	void SpawnNPC();

	/* Is Player nearby */
	bool IsPlayerNearby();
};
