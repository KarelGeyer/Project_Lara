#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimalAIController.generated.h"

class AAnimalBase;

UCLASS()
class PROJECT_LARA_API AAnimalAIController : public AAIController
{
	GENERATED_BODY()
public:
	/* A Constructor */
	AAnimalAIController();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	/*An Animal Instance*/
	AAnimalBase* Animal;

	/*Behavior Tree*/
	UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBehavior;

	/* Initialize AI*/
	void InitializeAI();

	/* Controlling Pawn Getter*/
	void GetBasePawn();
};
