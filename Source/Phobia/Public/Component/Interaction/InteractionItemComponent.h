#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionItemComponent.generated.h"

enum class ETriggerEvent : uint8;
class UInteractionOperatorBase;
class UInteractionEventBase;
class UInteractionConditionBase;
class UInteractionAbilityInfo;
class UInteractionAbilityDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractOnScene, ETriggerEvent, TriggerEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractOnHand, ETriggerEvent, TriggerEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractOnPut, ETriggerEvent, TriggerEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractOnDrop, ETriggerEvent, TriggerEvent);

// 可拾取物品的丢弃类型
UENUM(BlueprintType)
enum class EDropType : uint8
{
	None	UMETA(DisplayName = "空，无意义"),
	Trough	UMETA(DisplayName = "抛物线丢弃"),
	Drop	UMETA(DisplayName = "垂直丢弃"),
};

// 可交互物品的作用位置
UENUM(BlueprintType)
enum class EInteractionRoleType : uint8
{
	Scene	UMETA(DisplayName = "场景"),
	Hand	UMETA(DisplayName = "手上"),
};

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
	void InteractInScene(ETriggerEvent InTriggerEvent);

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInteractOnScene OnInteractOnScene;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Ability, meta = (DisplayName = "交互配置表"))
	TObjectPtr<UInteractionAbilityDataAsset> InteractionAbilityAsset;

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInteractionAbilityInfo>> AbilityInfos;
};
