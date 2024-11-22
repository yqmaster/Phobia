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
	void StartDoOperator(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	void EndDoOperator(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	/**
	 * 执行操作
	 */

	// C++ 实现开始执行操作
	virtual void DoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);


	// C++ 实现结束执行操作
	virtual void DoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);


	// 蓝图 实现开始执行操作
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Do Operator Begin"))
	void ReceiveDoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 实现结束执行操作
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Do Operator End"))
	void ReceiveDoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);
};
