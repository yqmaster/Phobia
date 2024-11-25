#pragma once

#include "CoreMinimal.h"
#include "Component/Character/Backpack/BackpackComponent.h"
#include "Component/Interaction/InteractionOperatorBase.h"
#include "InteractionOperator_DropItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, meta = (DisplayName = "拾取物品"))
class PHOBIA_API UInteractionOperator_DropItem : public UInteractionOperatorBase
{
	GENERATED_BODY()

public:
	static UInteractionOperator_DropItem* CreateDropItemOperator(EDropType InDropType);

private:
	// C++ 内部实现: 开始执行操作
	virtual void DoOperatorBegin(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

	// C++ 内部实现: 结束执行操作
	virtual void DoOperatorEnd(AActor* TakerActor, AActor* OwnerActor, UInteractionItemComponent* OwnerComponent) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否添加到无限背包"))
	EDropType DropType = EDropType::None;
};
