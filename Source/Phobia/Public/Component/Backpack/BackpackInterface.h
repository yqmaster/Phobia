#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BackpackInterface.generated.h"

class AActor;
class ACharacter;

UINTERFACE(MinimalAPI)
class UBackpackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PHOBIA_API IBackpackInterface
{
	GENERATED_BODY()

public:
	// 添加到背包
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAddToBackpack(AActor* InItem, ACharacter* TargetCharacter);
	virtual void OnAddToBackpack_Implementation(AActor* InItem, ACharacter* TargetCharacter) {}

	// 从背包中移除
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRemoveFromBackpack(AActor* InItem, ACharacter* TargetCharacter);
	virtual void OnRemoveFromBackpack_Implementation(AActor* InItem, ACharacter* TargetCharacter) {}

	// 设置到手中
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetToHand(AActor* InItem, ACharacter* TargetCharacter);
	virtual void OnSetToHand_Implementation(AActor* InItem, ACharacter* TargetCharacter) {}

	// 从手中移除
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUnSetFromHand(AActor* InItem, ACharacter* TargetCharacter);
	virtual void OnUnSetFromHand_Implementation(AActor* InItem, ACharacter* TargetCharacter) {}
};
