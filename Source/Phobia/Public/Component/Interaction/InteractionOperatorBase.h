#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionConfigBase.h"
#include "InteractionOperatorBase.generated.h"

/**
 *
 */
UCLASS(Blueprintable, abstract, EditInlineNew, ClassGroup = (Interaction))
class PHOBIA_API UInteractionOperatorBase : public UInteractionConfigBase
{
	GENERATED_BODY()

public:

	void StartDoOperator(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	void EndDoOperator(AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	/**
	 * 执行操作
	 */

	 // C++ 实现开始执行操作
	virtual void DoOperatorBegin(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {};

	// C++ 实现结束执行操作
	virtual void DoOperatorEnd(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {};

	// 蓝图 实现开始执行操作
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Do Operator Begin"))
	void ReceiveDoOperatorBegin(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 实现结束执行操作
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Do Operator End"))
	void ReceiveDoOperatorEnd(const AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);
};
