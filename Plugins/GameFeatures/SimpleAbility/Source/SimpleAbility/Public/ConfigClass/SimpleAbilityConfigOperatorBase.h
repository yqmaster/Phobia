#pragma once

#include "CoreMinimal.h"
#include "ConfigClass/SimpleAbilityConfigBase.h"
#include "SimpleAbilityConfigOperatorBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew, ClassGroup = (SimpleAbility))
class SIMPLEABILITY_API USimpleAbilityConfigOperatorBase : public USimpleAbilityConfigBase
{
	GENERATED_BODY()

public:
	// 外界调用: 开始执行操作
	void StartDoOperator(AActor* InCauser);
	// 外界调用: 结束执行操作
	void EndDoOperator(AActor* InCauser);

protected:
	// 内部实现: 当初始化的时候
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "InitOperator"))
	void ReceiveInitOperator(AActor* InOwner);
	virtual void InitOperator(AActor* InOwner) {}

	// 内部实现: 当反初始化的时候
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "UnInitOperator"))
	void ReceiveUnInitOperator(AActor* InOwner);
	virtual void UnInitOperator(AActor* InOwner) {}

	//  内部实现: 开始执行操作
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "DoOperatorBegin"))
	void ReceiveDoOperatorBegin(AActor* InOwner, AActor* InCauser);
	virtual void DoOperatorBegin(AActor* InOwner, AActor* InCauser) {}

	// 内部实现: 结束执行操作
	UFUNCTION(BlueprintImplementableEvent, Category = "SimpleAbility", meta = (DisplayName = "DoOperatorEnd"))
	void ReceiveDoOperatorEnd(AActor* InOwner, AActor* InCauser);
	virtual void DoOperatorEnd(AActor* InOwner, AActor* InCauser) {}

	virtual FString GetConfigCategory() const override final;

private:
	virtual void InitConfig(AActor* InOwner, USimpleAbilitySkill* InOwnerAbilitySkill) override final;
	virtual void UnInitConfig(AActor* InOwner) override final;
};
