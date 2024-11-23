#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionTypeDefine.h"
#include "Component/Interaction/InteractionEventBase.h"
#include "InteractionEvent_TriggerByInput.generated.h"

/**
 *
 */
UCLASS(Blueprintable, EditInlineNew, meta = (DisplayName = "被输入交互事件"))
class PHOBIA_API UInteractionEvent_TriggerByInput : public UInteractionEventBase
{
	GENERATED_BODY()

public:
	static UInteractionEvent_TriggerByInput* CreateTriggerByInputEvent(EInteractionEventType InTriggerType, EInteractionRoleType InRoleType);

protected:
	virtual void EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

	virtual void EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

private:
	UFUNCTION()
	void OnInteractionByClick(AActor* TakerActor, EInteractionRoleType InRoleType);

	UFUNCTION()
	void OnInteractionByPress(AActor* TakerActor, EInteractionRoleType InRoleType, bool IsStart);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "输入触发类型"))
	EInteractionEventType TriggerType = EInteractionEventType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "作用位置"))
	EInteractionRoleType RoleType = EInteractionRoleType::None;
};
