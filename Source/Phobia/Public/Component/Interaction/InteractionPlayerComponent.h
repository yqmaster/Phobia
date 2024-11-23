#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionPlayerComponent.generated.h"

class UInteractionItemComponent;
enum class EInteractionRoleType : uint8;

UCLASS(Blueprintable, abstract, ClassGroup = (Interaction))
class PHOBIA_API UInteractionPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionPlayerComponent();

	UFUNCTION(BlueprintCallable)
	void SetCurrentInteractionItem(UInteractionItemComponent* InInteractionItem);

	UFUNCTION(BlueprintCallable)
	void ClearCurrentInteractionItem();

	UFUNCTION(BlueprintCallable)
	void TriggerInteractionByClick(const EInteractionRoleType RoleType) const;

	UFUNCTION(BlueprintCallable)
	void TriggerInteractionByPress(const EInteractionRoleType RoleType, const bool IsStart);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Transient)
	TObjectPtr<UInteractionItemComponent> CurrentInteractionItem = nullptr;

	UPROPERTY(Transient)
	TMap<EInteractionRoleType, TObjectPtr<UInteractionItemComponent>> InteractionCachedItemMap;
};
