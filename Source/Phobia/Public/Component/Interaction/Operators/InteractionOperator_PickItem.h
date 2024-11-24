#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/InteractionOperatorBase.h"
#include "InteractionOperator_PickItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, meta = (DisplayName = "丢弃物品"))
class PHOBIA_API UInteractionOperator_PickItem : public UInteractionOperatorBase
{
	GENERATED_BODY()

public:
	static UInteractionOperator_PickItem* CreatePickItemOperator(bool bAddInfiniteBackpack);

private:
	// C++ 内部实现: 开始执行操作
	virtual void DoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

	// C++ 内部实现: 结束执行操作
	virtual void DoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否添加到无限背包"))
	bool bAddInfiniteBackpack = false;
};
