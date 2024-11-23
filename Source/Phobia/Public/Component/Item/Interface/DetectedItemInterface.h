// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DetectedItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDetectedItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 被检测物体执行接口
 */
class PHOBIA_API IDetectedItemInterface
{
	GENERATED_BODY()

public:
	/**
	 * 被检测执行
	 * @param bDetected 是否被检测
	 */
	virtual void OnDetected(bool bDetected) = 0;
};
