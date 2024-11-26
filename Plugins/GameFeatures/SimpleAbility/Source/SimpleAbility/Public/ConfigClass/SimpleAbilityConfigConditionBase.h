#pragma once

#include "CoreMinimal.h"
#include "ConfigClass/SimpleAbilityConfigBase.h"
#include "SimpleAbilityConfigConditionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew, ClassGroup = (SimpleAbility))
class SIMPLEABILITY_API USimpleAbilityConfigConditionBase : public USimpleAbilityConfigBase
{
	GENERATED_BODY()

public:
	// 外界调用: 条件检查
	bool CheckCondition(AActor* InCauser) const;

protected:
	// 内部实现: 当初始化的时候
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "InitCondition"))
	void ReceiveInitCondition(AActor* InOwner);
	virtual void InitCondition(AActor* InOwner) {}

	// 内部实现: 当反初始化的时候
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "UnInitCondition"))
	void ReceiveUnInitCondition(AActor* InOwner);
	virtual void UnInitCondition(AActor* InOwner) {}

	// 内部实现: 当进行条件检查
	UFUNCTION(BlueprintNativeEvent, Category = "SimpleAbility", meta = (DisplayName = "ConditionCheck"))
	bool ReceiveConditionCheck(AActor* InOwner, AActor* InCauser) const;
	virtual bool ConditionCheck(AActor* InOwner, AActor* InCauser) const;

	virtual FString GetConfigCategory() const override final;

private:
	virtual void InitConfig(AActor* InOwner, USimpleAbilitySkill* InOwnerAbilitySkill) override final;
	virtual void UnInitConfig(AActor* InOwner) override final;
};
