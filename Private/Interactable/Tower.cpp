// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable/Tower.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include <Project_Lara/PlayerCharacter.h>
#include "Kismet/GameplayStatics.h"


// Sets default values
ATower::ATower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	BrokenTowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrokenTowerMesh"));
	BrokenTowerMesh->SetupAttachment(BoxComponent);

	RepairedTowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RepairedTowerMesh"));
	RepairedTowerMesh->SetupAttachment(BoxComponent);
	RepairedTowerMesh->SetVisibility(false);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(BoxComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATower::OnInteractZoneEnter()
{
	if (BrokenTowerMesh->IsVisible()) {
		InteractionWidget->SetVisibility(true);
	}
}

void ATower::OnInteractZoneLeave()
{
	if (InteractionWidget->IsVisible()) {
		InteractionWidget->SetVisibility(false);
	}
}

void ATower::OnInteract()
{
	if (BrokenTowerMesh->IsVisible() && InteractionWidget->IsVisible()) {
		APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (Player == nullptr) {
			return;
		}

		FString ItemName = "Tower_Component";

		if (Player->FindItemInInventory(ItemName)) {
			BrokenTowerMesh->SetVisibility(false);
			RepairedTowerMesh->SetVisibility(true);
			InteractionWidget->SetVisibility(false);
			Player->RemoveItemFromInventory(ItemName);
		}
	}
}

