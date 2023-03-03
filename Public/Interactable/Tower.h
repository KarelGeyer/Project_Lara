// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction.h"
#include "Tower.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class PROJECT_LARA_API ATower : public AActor, public IInteraction
{
	GENERATED_BODY()

public:
	ATower();

protected:
	virtual void BeginPlay() override;

public:
	/*Box component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* BoxComponent;

	/* Static mesh for broken tower*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* BrokenTowerMesh;

	/* Static mesh for repaired tower*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* RepairedTowerMesh;

	/* An interaction Widget component*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
		UWidgetComponent* InteractionWidget;

	virtual void Tick(float DeltaTime) override;

private:
	// On enter interaction zone
	virtual void OnInteractZoneEnter() override;
	// On leave interaction zone
	virtual void OnInteractZoneLeave() override;
	// Interact
	virtual void OnInteract() override;
};
