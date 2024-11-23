#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionConfigBase.h"
#include "InteractionConditionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, abstract, EditInlineNew, ClassGroup = (Interaction))
class PHOBIA_API UInteractionConditionBase : public UInteractionConfigBase
{
	GENERATED_BODY()

public:
	// 外界调用: 条件检查
	bool CheckCondition(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	/**
	 * 条件检查
	 */

	// C++ 内部实现: 当进行条件检查
	virtual bool ConditionCheck(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 内部实现: 当进行条件检查
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Condition Check", ForceAsFunction))
	bool CallConditionCheck(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);
};
