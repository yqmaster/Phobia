#pragma once

#include "CoreMinimal.h"
#include "BackpackDefine.generated.h"

// 可拾取物品的丢弃类型
UENUM(BlueprintType)
enum class EDropType : uint8
{
	None UMETA(DisplayName = "空，无意义"),
	Trough UMETA(DisplayName = "抛物线丢弃"),
	Drop UMETA(DisplayName = "垂直丢弃"),
};
