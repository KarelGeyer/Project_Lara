// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable_Item.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include <Project_Lara/PlayerCharacter.h>
#include "Kismet/GameplayStatics.h"

APickable_Item::APickable_Item()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(BoxComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetVisibility(false);
}

void APickable_Item::BeginPlay()
{
	Super::BeginPlay();
}

void APickable_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickable_Item::OnInteractZoneEnter()
{
	InteractionWidget->SetVisibility(true);
}

void APickable_Item::OnInteractZoneLeave()
{
	if (InteractionWidget->IsVisible()) {
		InteractionWidget->SetVisibility(false);
	}
}

void APickable_Item::OnInteract()
{
	if (InteractionWidget->IsVisible()) {
		InteractionWidget->SetVisibility(false);
	}

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->AddItemToInventory(this);
		Destroy();
	}
}

FString APickable_Item::GetItemName()
{
	return Name;
}

