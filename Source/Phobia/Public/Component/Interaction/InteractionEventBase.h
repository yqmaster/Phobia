#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionConfigBase.h"
#include "InteractionEventBase.generated.h"

class UInteractionItemComponent;

// 输入触发类型
UENUM(BlueprintType)
enum class EInputTriggerType : uint8
{
	None	UMETA(DisplayName = "空，无意义"),
	Click	UMETA(DisplayName = "单击"),
	Press	UMETA(DisplayName = "长按"),
};

/**
 *
 */
UCLASS(Blueprintable, abstract, EditInlineNew, ClassGroup = (Interaction))
class PHOBIA_API UInteractionEventBase : public UInteractionConfigBase
{
	GENERATED_BODY()

public:
	virtual void EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	virtual void EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Event Active"))
	void ReceiveEventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Event DeActive"))
	void ReceiveEventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInputTriggerType InputType = EInputTriggerType::None;
};
