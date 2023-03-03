// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction.h"
#include "Interfaces/PickableItem.h"
#include "Pickable_Item.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class PROJECT_LARA_API APickable_Item : public AActor, public IInteraction, public IPickableItem
{
	GENERATED_BODY()

public:
	APickable_Item();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Name")
		FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* ItemMesh;

	/* An interaction Widget component*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
		UWidgetComponent* InteractionWidget;

private:
	// On enter interaction zone
	virtual void OnInteractZoneEnter() override;
	// On leave interaction zone
	virtual void OnInteractZoneLeave() override;
	// Interact
	virtual void OnInteract() override;
	// Return Item Name
	virtual FString GetItemName() override;
};
