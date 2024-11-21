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
	// 激活
	void ActiveEvent(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 注销
	void DeActiveEvent(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	/**
	 * 事件激活
	 */

	// C++ 实现当事件激活
	virtual void EventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent){};

	// C++ 实现当事件注销
	virtual void EventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent){};

	// 蓝图 实现当事件激活
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Event Active"))
	void ReceiveEventActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 实现当事件注销
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Event DeActive"))
	void ReceiveEventDeActive(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	/**
	 * 事件触发时调用的函数
	 */

	// C++ 在事件开始触发时调用
	void TriggerEventStart();

	// C++ 在事件结束触发时调用
	void TriggerEventEnd();


	// 蓝图 在事件开始触发时调用
	UFUNCTION(BlueprintCallable)
	void CallTriggerEventStart();

	// 蓝图 在事件结束触发时调用
	UFUNCTION(BlueprintCallable)
	void CallTriggerEventEnd();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInputTriggerType InputType = EInputTriggerType::None;
};
