#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionConfigBase.h"
#include "InteractionEventBase.generated.h"

/**
 *
 */
UCLASS(Blueprintable, abstract, EditInlineNew, ClassGroup = (Interaction))
class PHOBIA_API UInteractionEventBase : public UInteractionConfigBase
{
	GENERATED_BODY()

public:
	// 外界调用: 事件可以激活了
	void ActiveEvent(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 外界调用: 事件可以注销
	void DeActiveEvent(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	/**
	 * 事件激活
	 */

	// C++ 内部实现: 当事件激活
	virtual void EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {}

	// C++ 内部实现: 当事件注销
	virtual void EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {}

	// 蓝图 内部实现: 当事件激活
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Event Active", ForceAsFunction))
	void ReceiveEventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 内部实现: 当事件注销
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Event DeActive", ForceAsFunction))
	void ReceiveEventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	/**
	 * 事件触发时调用的函数
	 */

	// C++ 内部调用: 在事件开始触发时调用
	void TriggerEventStart(AActor* TakerActor) const;

	// C++ 内部调用: 在事件结束触发时调用
	void TriggerEventEnd(AActor* TakerActor) const;

	// 蓝图 内部调用: 在事件开始触发时调用
	UFUNCTION(BlueprintCallable)
	void CallTriggerEventStart(AActor* TakerActor);

	// 蓝图 内部调用: 在事件结束触发时调用
	UFUNCTION(BlueprintCallable)
	void CallTriggerEventEnd(AActor* TakerActor);
};
