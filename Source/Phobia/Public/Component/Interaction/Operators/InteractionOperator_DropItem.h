#pragma once

#include "CoreMinimal.h"
#include "Component/Backpack/BackpackDefine.h"
#include "ConfigClass/SimpleAbilityConfigOperatorBase.h"
#include "InteractionOperator_DropItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, meta = (DisplayName = "拾取物品"))
class PHOBIA_API UInteractionOperator_DropItem : public USimpleAbilityConfigOperatorBase
{
	GENERATED_BODY()

public:
	static UInteractionOperator_DropItem* CreateDropItemOperator(EDropType InDropType);

private:
	virtual void DoOperatorBegin(AActor* InOwner, AActor* InCauser) override;
	virtual void DoOperatorEnd(AActor* InOwner, AActor* InCauser) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否添加到无限背包"))
	EDropType DropType = EDropType::None;
};
