// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UBoxComponent;
class IInteraction;
class IPickableItem;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UENUM(Category = "Stats")
enum class EStatsType
{
	Health,
	Stamina
};

UCLASS(config = Game)
class PROJECT_LARA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Pawn mesh: 1st person view (arms; seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
		FOnUseItem OnUseItem;

	/* An interaction box*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UBoxComponent* InteractionBox;

	/*Player HUD Widget class*/
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerHUDClass;

	/* Health and Stamina setter*/
	UFUNCTION()
		void SetStats(EStatsType StatsType, float Value);

protected:

	/** Fires a projectile. */
	void OnPrimaryAction();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData TouchItem;

private:
	/*Base health value of the player*/
	float Health = 100.f;

	/*Base stamina value of the player*/
	float Stamina = 100.f;

	/* Represents wheter player is in interaction box*/
	bool bCanInteract = false;

	/* An Actor to interact with*/
	IInteraction* Interactable;

	/*Player HUD Widget*/
	UUserWidget* PlayerHUD;

	/* List of pickedup Items*/
	TArray<IPickableItem*> PickedUpItems;

	// Trigger when player enters the interaction box
	UFUNCTION()
		void OnInteractionBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Trigger when player leaves the interaction box
	UFUNCTION()
		void OnInteractionBoxOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/* Interaction Handler*/
	void Interact();

	/* Add item to Inventory*/
	void AddItemToInventory(IPickableItem* Item);

	/* Remove Item found by name from Inventory*/
	void RemoveItemFromInventory(IPickableItem* Item);

	/* Remove Item found by name from Inventory*/
	void RemoveItemFromInventory(FString ItemName);

	/* Find item in inventory*/
	bool FindItemInInventory(FString ItemName);

	/*Triggeres when the Player character is damaged by other pawns*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};

