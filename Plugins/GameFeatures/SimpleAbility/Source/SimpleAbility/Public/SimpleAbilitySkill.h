#pragma once

#include "CoreMinimal.h"
#include "ConfigClass/SimpleAbilityConfigBase.h"
#include "SimpleAbilitySkill.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(SimpleAbility, Log, All);

class USimpleAbilityConfigBase;
class USimpleAbilityConfigEventBase;
class USimpleAbilityConfigConditionBase;
class USimpleAbilityConfigOperatorBase;

/**
 * 
 */
UCLASS(ClassGroup = (SimpleAbility))
class SIMPLEABILITY_API USimpleAbilitySkill : public UObject
{
	GENERATED_BODY()

public:
	// 创建一个 AbilitySkill
	static USimpleAbilitySkill* CreateSkill(const USimpleAbilityConfigEventBase* InEvent, const TArray<USimpleAbilityConfigConditionBase*>& InConditions, const TArray<USimpleAbilityConfigOperatorBase*>& InOperators, AActor* InOwnerActor, FString& InSkillName);
	// 激活一个 AbilitySkill
	static void ActiveSkill(const USimpleAbilitySkill* InAbilitySkill);
	// 销毁一个 AbilitySkill
	static void DestroySkill(USimpleAbilitySkill* InAbilitySkill);

	// Event 调用: 事件开始触发
	void TriggerEventStart(AActor* InCauserActor);
	// Event 调用: 事件结束触发
	void TriggerEventEnd(AActor* InCauserActor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetSkillName() const;

private:
	// 初始化 AbilitySkill
	void InitConfigs();
	// 逆初始化 AbilitySkill
	void UnInitConfigs();

	// 激活 AbilitySkill
	void ActiveAbilitySkill() const;
	// 注销 AbilitySkill
	void DeActiveAbilitySkill() const;

	// 深拷贝一个 Config 数组
	template <typename InConfigType>
	static TArray<InConfigType*> DuplicateConfigArray(const TArray<InConfigType*>& InArray);
	// 深拷贝一个 Config 对象
	template <typename InConfigType>
	static InConfigType* DuplicateConfig(const InConfigType* InConfig);

protected:
	UPROPERTY(Transient)
	TObjectPtr<USimpleAbilityConfigEventBase> Event;

	UPROPERTY(Transient)
	TArray<TObjectPtr<USimpleAbilityConfigConditionBase>> Conditions;

	UPROPERTY(Transient)
	TArray<TObjectPtr<USimpleAbilityConfigOperatorBase>> Operators;

	UPROPERTY(Transient)
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(Transient)
	FString AbilitySkillName;
};

template <typename InObjectType>
TArray<InObjectType*> USimpleAbilitySkill::DuplicateConfigArray(const TArray<InObjectType*>& InArray)
{
	TArray<InObjectType*> NewArray;
	for (int32 i = 0; i < InArray.Num(); ++i)
	{
		if (InArray[i])
		{
			InObjectType* NewObj = DuplicateObject<InObjectType>(InArray[i], nullptr);

			// 设置 ConfigIndex
			if (USimpleAbilityConfigBase* Config = Cast<USimpleAbilityConfigBase>(NewObj))
			{
				Config->SetConfigIndex(i);
			}

			NewArray.Add(NewObj);
		}
	}

	for (const InObjectType* OldObj : InArray)
	{
		if (OldObj)
		{
			NewArray.Add(DuplicateObject<InObjectType>(OldObj, nullptr));
		}
	}
	return NewArray;
}

template <typename InConfigType>
InConfigType* USimpleAbilitySkill::DuplicateConfig(const InConfigType* InConfig)
{
	return DuplicateObject<InConfigType>(InConfig, nullptr);
}
