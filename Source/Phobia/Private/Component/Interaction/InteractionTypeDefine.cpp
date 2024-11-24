#include "Component/Interaction/InteractionTypeDefine.h"

FString UInteractionFunctionLibrary::EInteractionRoleTypeToString(const EInteractionRoleType InRoleType)
{
	switch (InRoleType)
	{
	case EInteractionRoleType::None:
		return TEXT("无意义");
	case EInteractionRoleType::Scene:
		return TEXT("场景");
	case EInteractionRoleType::Hand:
		return TEXT("手上");
	case EInteractionRoleType::Pick:
		return TEXT("拾取");
	case EInteractionRoleType::Drop:
		return TEXT("丢弃");
	case EInteractionRoleType::Put:
		return TEXT("放置");
	default:
		ensureAlwaysMsgf(false, TEXT("UAutomationBlueprintFunctionLibrary::EInteractionRoleTypeToString: Invalid EInteractionRoleType"));
		return TEXT("无效类型");
	}
}
