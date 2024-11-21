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
	bool CheckCondition(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	/**
	 * 条件检查
	 */

	// C++ 实现当事件激活
	virtual bool ConditionCheck(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 实现当事件激活
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Condition Check"))
	bool CallConditionCheck(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);
};
