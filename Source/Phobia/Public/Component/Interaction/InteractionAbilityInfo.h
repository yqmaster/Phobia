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
	// 初始化 AbilityInfo
	void InitAbilityInfo(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);
	// 释放 AbilityInfo
	void UnInitAbilityInfo(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

public:
	// TODO 这里的宏都是中间产物，写完后可以都删了，应该也没有其他地方需要 New 一个 UInteractionAbilityInfo 了
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TObjectPtr<UInteractionEventBase> Event = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TArray<TObjectPtr<UInteractionConditionBase>> Conditions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> Operators;
};