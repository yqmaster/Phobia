#pragma once

#include "CoreMinimal.h"
#include "ConfigClass/SimpleAbilityConfigOperatorBase.h"
#include "InteractionOperator_PickItem.generated.h"

class UBackpackComponent;

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, meta = (DisplayName = "丢弃物品"))
class PHOBIA_API UInteractionOperator_PickItem : public USimpleAbilityConfigOperatorBase
{
	GENERATED_BODY()

public:
	static UInteractionOperator_PickItem* CreatePickItemOperator(bool bAddInfiniteBackpack);

private:
	virtual void DoOperatorBegin(AActor* InOwner, AActor* InCauser) override;
	virtual void DoOperatorEnd(AActor* InOwner, AActor* InCauser) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否添加到无限背包"))
	bool bAddInfiniteBackpack = false;
};
