#include "NPC/Characters/NPC_Character.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

ANPC_Character::ANPC_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateAttachments();
}

void ANPC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPC_Character::BeginPlay()
{
	Super::BeginPlay();
}

void ANPC_Character::CreateAttachments()
{
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	if (InteractionWidget) {
		InteractionWidget->SetupAttachment(RootComponent);
		InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
		InteractionWidget->SetVisibility(false);
	}

	DialogWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DialogWidget"));
	if (DialogWidget) {
		DialogWidget->SetupAttachment(RootComponent);
		DialogWidget->SetWidgetSpace(EWidgetSpace::Screen);
		DialogWidget->SetVisibility(false);
	}
}

void ANPC_Character::SetDialogueText(FString Text)
{
	UTextBlock* TextBlock = Cast<UTextBlock>(DialogWidget->GetUserWidgetObject()->GetWidgetFromName("Dialog"));
	if (TextBlock) {
		TextBlock->SetText(FText::FromString(Text));
	}
}

void ANPC_Character::OnInteractZoneEnter()
{
	InteractionWidget->SetVisibility(true);
}

void ANPC_Character::OnInteractZoneLeave()
{
	if (InteractionWidget->IsVisible()) {
		InteractionWidget->SetVisibility(false);
	}

	if (DialogWidget->IsVisible()) {
		DialogWidget->SetVisibility(false);
	}

	DialogState = 0;
}

void ANPC_Character::OnInteract()
{
	if (DialogWidget == nullptr) {
		return;
	}

	if (DialogText.IsValidIndex(DialogState)) {
		DialogWidget->SetVisibility(true);

		SetDialogueText(DialogText[DialogState]);
		DialogState++;

		if (InteractionWidget->IsVisible()) {
			InteractionWidget->SetVisibility(false);
		}
	}
	else {
		DialogWidget->SetVisibility(false);
		InteractionWidget->SetVisibility(true);
		DialogState = 0;
	}
}
