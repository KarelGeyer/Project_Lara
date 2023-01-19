#include "SpawnPoint/SpawnPoint.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NPC/NPC_Base.h"
#include "AIController.h"
#include "Animals/AnimalBase.h"


ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnNPC();
}

void ASpawnPoint::SpawnNPC()
{
	if (AIControllerClass != nullptr && IsPlayerNearby() && !bIsNPCSpawned)
	{
		AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, GetActorLocation(), GetActorRotation());

		if (ClassToSpawn != nullptr) {
			NPCToSpawn = GetWorld()->SpawnActor<ANPC_Base>(ClassToSpawn, GetActorLocation(), GetActorRotation());

			if (NPCToSpawn == nullptr)
			{
				return;
			}

			NPCToSpawn->SetActorLocation(GetActorLocation());
			NPCToSpawn->SetActorRotation(GetActorRotation());
			NPCToSpawn->SetPatrolLocation(SpawnNpcPatrolLocation);

			AIController->Possess(NPCToSpawn);
		}

		bIsNPCSpawned = true;

		return;
	}

	if (!IsPlayerNearby() && bIsNPCSpawned && AIController != nullptr && NPCToSpawn != nullptr)
	{
		NPCToSpawn->Destroy();
		AIController->Destroy();
		bIsNPCSpawned = false;

		return;
	}
}

bool ASpawnPoint::IsPlayerNearby()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector NewPlayerLocation = PlayerPawn->GetActorLocation();
	FVector Location = GetActorLocation();

	float Distance = FVector::Dist(Location, NewPlayerLocation);

	return Distance < RenderDistance;
}

