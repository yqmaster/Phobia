#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DetectedItemInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UDetectedItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 被检测物体执行接口
 */
class IDetectedItemInterface
{
	GENERATED_BODY()

public:
	/**
	 * 被检测执行
	 * @param InTaker 检测发起者
	 * @param bDetected 是否被检测
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "On Detected", ForceAsFunction))
	void OnDetected(AActor* InTaker, bool bDetected);
	virtual void OnDetected_Implementation(AActor* InTaker, bool bDetected) {}
};
