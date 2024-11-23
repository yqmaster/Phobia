#pragma once

#include "CoreMinimal.h"
#include "InteractionConfigBase.generated.h"

class UInteractionItemComponent;
class UInteractionAbilityInfo;

/**
 * 
 */
UCLASS(BlueprintType, Abstract, ClassGroup = (Interaction))
class PHOBIA_API UInteractionConfigBase : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * 外界调用的初始化接口
	 */

	// 外界调用: 初始化
	void Init(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent, UInteractionAbilityInfo* OwnerAbilityInfo);

	// 外界调用: 逆初始化
	void UnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent, UInteractionAbilityInfo* OwnerAbilityInfo);

protected:
	/**
	 * 内部实现的初始化方法
	 */

	// C++ 内部实现: 当初始化的时候
	virtual void OnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {}

	// C++ 内部实现: 当反初始化的时候
	virtual void OnUnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {}

	// 蓝图 内部实现: 当初始化的时候
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Init", ForceAsFunction))
	void ReceiveOnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 内部实现: 当反初始化的时候
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On UnInit", ForceAsFunction))
	void ReceiveOnUnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	// Owner
	UPROPERTY(Transient)
	TObjectPtr<UInteractionAbilityInfo> AbilityInfo;
};
