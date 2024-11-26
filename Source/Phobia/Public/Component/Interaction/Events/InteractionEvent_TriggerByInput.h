#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionTypeDefine.h"
#include "ConfigClass/SimpleAbilityConfigEventBase.h"
#include "InteractionEvent_TriggerByInput.generated.h"

class UInteractionItemComponent;

/**
 *
 */
UCLASS(Blueprintable, EditInlineNew, meta = (DisplayName = "被输入交互事件"))
class PHOBIA_API UInteractionEvent_TriggerByInput : public USimpleAbilityConfigEventBase
{
	GENERATED_BODY()

public:
	static UInteractionEvent_TriggerByInput* CreateTriggerByInputEvent(EInteractionEventType InTriggerType, EInteractionRoleType InRoleType);

protected:
	virtual void InitEvent(AActor* InOwner) override;
	virtual void UnInitEvent(AActor* InOwner) override;

	virtual void EventActive(const AActor* InOwner) override;
	virtual void EventDeActive(const AActor* InOwner) override;

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

private:
	UPROPERTY(Transient)
	TObjectPtr<UInteractionItemComponent> ItemComponent = nullptr;
};
