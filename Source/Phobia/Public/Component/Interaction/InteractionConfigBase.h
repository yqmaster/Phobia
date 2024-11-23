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

	// 外界调用的初始化
	void Init(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent, UInteractionAbilityInfo* OwnerAbilityInfo);
	// 外界调用的逆初始化
	void UnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent, UInteractionAbilityInfo* OwnerAbilityInfo);

protected:
	/**
	 * 内部实现的初始化方法
	 */

	// 当初始化的时候
	virtual void OnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 当反初始化的时候
	virtual void OnUnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 当初始化的时候
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Init"))
	void ReceiveOnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 当反初始化的时候
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On UnInit"))
	void ReceiveOnUnInit(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	UPROPERTY(Transient)
	TObjectPtr<UInteractionAbilityInfo> AbilityInfo;
};
