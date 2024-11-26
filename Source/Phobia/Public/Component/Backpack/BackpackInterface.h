#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BackpackInterface.generated.h"

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
	void OnAddToBackpack(ACharacter* InTarget, AActor* InItem);
	virtual void OnAddToBackpack_Implementation(ACharacter* InTarget, AActor* InItem) {}

	// 从背包中移除
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRemoveFromBackpack(ACharacter* InTarget, AActor* InItem);
	virtual void OnRemoveFromBackpack_Implementation(ACharacter* InTarget, AActor* InItem) {}

	// 设置到手中
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetToHand(ACharacter* InTarget, AActor* InItem);
	virtual void OnSetToHand_Implementation(ACharacter* InTarget, AActor* InItem) {}

	// 从手中移除
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUnSetFromHand(ACharacter* InTarget, AActor* InItem);
	virtual void OnUnSetFromHand_Implementation(ACharacter* InTarget, AActor* InItem) {}
};
