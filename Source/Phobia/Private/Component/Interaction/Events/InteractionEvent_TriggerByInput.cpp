#include "Component/Interaction/Events/InteractionEvent_TriggerByInput.h"

#include "Component/Interaction/InteractionItemComponent.h"

UInteractionEvent_TriggerByInput* UInteractionEvent_TriggerByInput::CreateTriggerByInputEvent(const EInteractionEventType InTriggerType, const EInteractionRoleType InRoleType)
{
	UInteractionEvent_TriggerByInput* Event = NewObject<UInteractionEvent_TriggerByInput>();
	Event->TriggerType = InTriggerType;
	Event->RoleType = InRoleType;
	return Event;
}

void UInteractionEvent_TriggerByInput::InitEvent(AActor* InOwner)
{
	Super::InitEvent(InOwner);

	ItemComponent = InOwner->FindComponentByClass<UInteractionItemComponent>();
	if (!ItemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Init failed, [%s] does not have UInteractionItemComponent"), *GetConfigInfo(), *InOwner->GetName());
	}
}

void UInteractionEvent_TriggerByInput::UnInitEvent(AActor* InOwner)
{
	ItemComponent = nullptr;

	Super::UnInitEvent(InOwner);
}

void UInteractionEvent_TriggerByInput::EventActive(const AActor* InOwner)
{
	Super::EventActive(InOwner);

	if (ItemComponent)
	{
		switch (TriggerType)
		{
		case EInteractionEventType::None:
			UE_LOG(LogTemp, Warning, TEXT("UInteractionEvent_TriggerInScene::EventActive TriggerType is None"));
			break;
		case EInteractionEventType::Click:
			ItemComponent->OnInteractByClick.AddDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByClick);
			break;
		case EInteractionEventType::Press:
			ItemComponent->OnInteractByPress.AddDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByPress);
			break;
		default: ;
			UE_LOG(LogTemp, Warning, TEXT("Invalid TriggerType"));
		}
	}
}

void UInteractionEvent_TriggerByInput::EventDeActive(const AActor* InOwner)
{
	if (ItemComponent)
	{
		switch (TriggerType)
		{
		case EInteractionEventType::None:
			UE_LOG(LogTemp, Warning, TEXT("UInteractionEvent_TriggerInScene::EventActive TriggerType is None"));
			break;
		case EInteractionEventType::Click:
			ItemComponent->OnInteractByClick.RemoveDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByClick);
			break;
		case EInteractionEventType::Press:
			ItemComponent->OnInteractByPress.RemoveDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByPress);
			break;
		default: ;
			UE_LOG(LogTemp, Warning, TEXT("Invalid TriggerType"));
		}
	}

	Super::EventDeActive(InOwner);
}

void UInteractionEvent_TriggerByInput::OnInteractionByClick(AActor* TakerActor, const EInteractionRoleType InRoleType)
{
	if (InRoleType == RoleType)
	{
		TriggerEventStart(TakerActor);
		TriggerEventEnd(TakerActor);
	}
}

void UInteractionEvent_TriggerByInput::OnInteractionByPress(AActor* TakerActor, const EInteractionRoleType InRoleType, const bool IsStart)
{
	if (InRoleType == RoleType)
	{
		if (IsStart)
		{
			TriggerEventStart(TakerActor);
		}
		else
		{
			TriggerEventEnd(TakerActor);
		}
	}
}
