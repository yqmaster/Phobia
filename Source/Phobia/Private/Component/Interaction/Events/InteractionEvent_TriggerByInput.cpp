#include "Component/Interaction/Events/InteractionEvent_TriggerByInput.h"

#include "Component/Interaction/InteractionItemComponent.h"

void UInteractionEvent_TriggerByInput::EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	Super::EventActive(OwnerActor, OwnerComponent);

	if (OwnerComponent)
	{
		switch (TriggerType)
		{
		case EInteractionEventType::None:
			UE_LOG(LogTemp, Warning, TEXT("UInteractionEvent_TriggerInScene::EventActive TriggerType is None"));
			break;
		case EInteractionEventType::Click:
			OwnerComponent->OnInteractByClick.AddDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByClick);
			break;
		case EInteractionEventType::Press:
			OwnerComponent->OnInteractByPress.AddDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByPress);
			break;
		default: ;
			UE_LOG(LogTemp, Warning, TEXT("Invalid TriggerType"));
		}
	}
}

void UInteractionEvent_TriggerByInput::EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent)
{
	if (OwnerComponent)
	{
		switch (TriggerType)
		{
		case EInteractionEventType::None:
			UE_LOG(LogTemp, Warning, TEXT("UInteractionEvent_TriggerInScene::EventActive TriggerType is None"));
			break;
		case EInteractionEventType::Click:
			OwnerComponent->OnInteractByClick.RemoveDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByClick);
			break;
		case EInteractionEventType::Press:
			OwnerComponent->OnInteractByPress.RemoveDynamic(this, &UInteractionEvent_TriggerByInput::OnInteractionByPress);
			break;
		default: ;
			UE_LOG(LogTemp, Warning, TEXT("Invalid TriggerType"));
		}
	}

	Super::EventDeActive(OwnerActor, OwnerComponent);
}

void UInteractionEvent_TriggerByInput::OnInteractionByClick(AActor* TakerActor, EInteractionRoleType InRoleType)
{
	if (InRoleType == RoleType)
	{
		TriggerEventStart(TakerActor);
		TriggerEventEnd(TakerActor);
	}
}

void UInteractionEvent_TriggerByInput::OnInteractionByPress(AActor* TakerActor, EInteractionRoleType InRoleType, bool IsStart)
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
