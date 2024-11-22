#pragma once

#include "CoreMinimal.h"

// 可交互物品的交互事件类型
UENUM(BlueprintType)
enum class EInteractionEventType : uint8
{
	None UMETA(DisplayName = "空，无意义"),
	Click UMETA(DisplayName = "单击"),
	Press UMETA(DisplayName = "长按"),
};

// 可交互物品的作用位置
UENUM(BlueprintType)
enum class EInteractionRoleType : uint8
{
	None UMETA(DisplayName = "空，无意义"),
	Scene UMETA(DisplayName = "场景"),
	Hand UMETA(DisplayName = "手上"),
	Pick UMETA(DisplayName = "拾取"),
	Drop UMETA(DisplayName = "丢弃"),
	Put UMETA(DisplayName = "放置"),
};
