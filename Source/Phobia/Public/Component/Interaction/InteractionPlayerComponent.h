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
	void SetCurrentInteractionItem(const EInteractionRoleType InRoleType, UInteractionItemComponent* InInteractionItem);

	UFUNCTION(BlueprintCallable)
	void ClearCurrentInteractionItem(const EInteractionRoleType InRoleType);

	UFUNCTION(BlueprintCallable)
	void TriggerInteractionByClick(const EInteractionRoleType RoleType) const;

	UFUNCTION(BlueprintCallable)
	void TriggerInteractionByPress(const EInteractionRoleType RoleType, const bool IsStart);

protected:
	UInteractionItemComponent* FindInItemMap(const EInteractionRoleType RoleType) const;
	UInteractionItemComponent* FindInCachedItemMap(const EInteractionRoleType RoleType) const;

private:
	UPROPERTY(Transient)
	TMap<EInteractionRoleType, TObjectPtr<UInteractionItemComponent>> InteractionItemMap;

	UPROPERTY(Transient)
	TMap<EInteractionRoleType, TObjectPtr<UInteractionItemComponent>> InteractionCachedItemMap;
};
