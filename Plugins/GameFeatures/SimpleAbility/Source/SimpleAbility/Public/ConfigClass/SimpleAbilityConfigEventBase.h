#pragma once

#include "CoreMinimal.h"
#include "SimpleAbilityConfigBase.h"
#include "SimpleAbilityConfigEventBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, abstract, EditInlineNew, ClassGroup = (SimpleAbility))
class SIMPLEABILITY_API USimpleAbilityConfigEventBase : public USimpleAbilityConfigBase
{
	GENERATED_BODY()

public:
	// 外界调用: 事件可以激活了
	void ActiveEvent();

	// 外界调用: 事件可以注销
	void DeActiveEvent();

protected:
	// 内部实现: 当初始化的时候
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "InitEvent"))
	void ReceiveInitEvent(AActor* InOwner);
	virtual void InitEvent(AActor* InOwner) {}

	// 内部实现: 当反初始化的时候
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "UnInitEvent"))
	void ReceiveUnInitEvent(AActor* InOwner);
	virtual void UnInitEvent(AActor* InOwner) {}

	// 内部实现: 当事件激活
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "EventActive"))
	void ReceiveEventActive(const AActor* InOwner);
	virtual void EventActive(const AActor* InOwner) {}

	// 内部实现: 当事件注销
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "EventDeActive"))
	void ReceiveEventDeActive(const AActor* InOwner);
	virtual void EventDeActive(const AActor* InOwner) {}

	// 内部调用: 在事件开始触发时调用
	UFUNCTION(BlueprintCallable, Category = "SimpleAbility")
	void TriggerEventStart(AActor* InCauser) const;

	// 内部调用: 在事件结束触发时调用
	UFUNCTION(BlueprintCallable, Category = "SimpleAbility")
	void TriggerEventEnd(AActor* InCauser) const;

	virtual FString GetConfigCategory() const override final;

private:
	virtual void InitConfig(AActor* InOwner, USimpleAbilitySkill* InOwnerSkill) override final;
	virtual void UnInitConfig(AActor* InOwner) override final;
};
