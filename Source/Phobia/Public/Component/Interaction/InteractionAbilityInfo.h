#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionAbilityInfo.generated.h"

class UInteractionItemComponent;
class UInteractionOperatorBase;
class UInteractionEventBase;
class UInteractionConditionBase;

UCLASS(Blueprintable, EditInlineNew, ClassGroup = (Interaction))
class PHOBIA_API UInteractionAbilityInfo : public UObject
{
	GENERATED_BODY()

public:
	// 创建一个 AbilityInfo
	static UInteractionAbilityInfo* CreateAbilityInfo(UInteractionEventBase* InEvent, const TArray<UInteractionConditionBase*>& InConditions, const TArray<UInteractionOperatorBase*>& InOperators);
	// 创建一个 AbilityInfo，并且复制 Event、Conditions、Operators
	static UInteractionAbilityInfo* CreateAbilityInfoWithCopy(const UInteractionEventBase* InEvent, const TArray<UInteractionConditionBase*>& InConditions, const TArray<UInteractionOperatorBase*>& InOperators);

	// 初始化 AbilityInfo
	void InitAbilityInfo(AActor* InOwnerActor, UInteractionItemComponent* InOwnerComponent);
	// 逆初始化 AbilityInfo
	void UnInitAbilityInfo(AActor* InOwnerActor, UInteractionItemComponent* InOwnerComponent);

	// 激活 AbilityInfo
	void ActiveAbilityInfo() const;
	// 注销 AbilityInfo
	void DeActiveAbilityInfo() const;

	// 触发事件开始
	void TriggerAbilityInfoEventStart(AActor* TakerActor);
	// 触发事件结束
	void TriggerAbilityInfoEventEnd(AActor* TakerActor);

private:
	// 深拷贝一个 TObjectPtr 数组
	template <typename InObjectType>
	static TArray<InObjectType*> DuplicateTObjectArray(const TArray<InObjectType*>& InArray);

protected:
	UPROPERTY(Transient)
	TObjectPtr<UInteractionEventBase> Event = nullptr;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UInteractionConditionBase>> Conditions;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UInteractionOperatorBase>> Operators;

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInteractionOperatorBase>> StartingOperators;

	UPROPERTY(Transient)
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(Transient)
	TObjectPtr<UInteractionItemComponent> OwnerComponent;
};

template <typename InObjectType>
TArray<InObjectType*> UInteractionAbilityInfo::DuplicateTObjectArray(const TArray<InObjectType*>& InArray)
{
	TArray<InObjectType*> NewArray;
	for (const InObjectType* OldObj : InArray)
	{
		NewArray.Add(DuplicateObject<InObjectType>(OldObj, nullptr));
	}
	return NewArray;
}
