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
	// 外界调用: 开始执行操作
	void StartDoOperator(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);
	// 外界调用: 结束执行操作
	void EndDoOperator(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

protected:
	/**
	 * 执行操作
	 */

	// C++ 内部实现: 开始执行操作
	virtual void DoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {}

	// C++ 内部实现: 结束执行操作
	virtual void DoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) {}

	// 蓝图 内部实现: 开始执行操作
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Do Operator Begin"))
	void ReceiveDoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);

	// 蓝图 内部实现: 结束执行操作
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Do Operator End"))
	void ReceiveDoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent);
};
