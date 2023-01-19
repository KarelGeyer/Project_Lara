// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPC_Base.h"
#include "UObject/Interface.h"
#include "Interfaces/Interaction.h"
#include "NPC_Character.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class PROJECT_LARA_API ANPC_Character : public ANPC_Base, public IInteraction
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* An interaction Widget component*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UWidgetComponent* InteractionWidget;

	/* An interaction Widget component*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UWidgetComponent* DialogWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	// Create Attachments
	void CreateAttachments();

	// On enter interaction zone
	virtual void OnInteractZoneEnter() override;
	// On leave interaction zone
	virtual void OnInteractZoneLeave() override;
	// Interact
	virtual void OnInteract() override;
};