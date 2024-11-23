#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionItemComponent.generated.h"

enum class EInteractionRoleType : uint8;
class UInteractionAbilityInfo;
class UInteractionAbilityDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractByClick, AActor*, TakerActor, EInteractionRoleType, RoleType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInteractByPress, AActor*, TakerActor, EInteractionRoleType, RoleType, bool, IsStart);

UCLASS(Blueprintable, abstract, ClassGroup = (Interaction))
class PHOBIA_API UInteractionItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionItemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void TakeInteractionByClick(AActor* Taker, EInteractionRoleType RoleType) const;

	UFUNCTION(BlueprintCallable)
	void TakeInteractionByPress(AActor* Taker, EInteractionRoleType RoleType, bool IsStart) const;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInteractByClick OnInteractByClick;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInteractByPress OnInteractByPress;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Ability, meta = (DisplayName = "交互配置表"))
	TObjectPtr<UInteractionAbilityDataAsset> InteractionAbilityAsset;

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInteractionAbilityInfo>> AbilityInfos;
};
