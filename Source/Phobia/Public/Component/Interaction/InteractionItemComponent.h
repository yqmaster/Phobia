#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionItemComponent.generated.h"

enum class ETriggerEvent : uint8;
class UInteractionOperatorBase;
class UInteractionEventBase;
class UInteractionConditionBase;
class UInteractionAbilityInfo;

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

	// 拾取/丢弃/放置

	// 是否能被拾取
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否能拾取丢弃"))
	bool bCanBePick = false;

	// 拾取的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "拾取的额外效果", EditCondition = "bCanBePick", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> PickOperators;

	// 丢弃时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "丢弃的方式", EditCondition = "bCanBePick", EditConditionHides))
	EDropType DropType = EDropType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "是否能被放置", EditCondition = "bCanBePick", EditConditionHides))
	bool bCanBePut = false;

	// 放置的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "放置条件", EditCondition = "bCanBePick && bCanBePut", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionConditionBase>> PutConditions;

	// 放置的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "放置的效果", EditCondition = "bCanBePick && bCanBePut", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> PutOperators;

	// 点击

	// 是否能被点击
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "能否被点击"))
	bool bCanBeClick = false;

	// 点击前的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击条件", EditCondition = "bCanBeClick", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionConditionBase>> ClickConditions;

	// 点击时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击效果", EditCondition = "bCanBeClick", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> ClickOperators;

	// 点击可作用的地方
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "点击可作用的地方", EditCondition = "bCanBeClick", EditConditionHides))
	TArray<EInteractionRoleType> ClickRoleType;

	// 长按

	// 是否能被长按
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "能否被长按"))
	bool bCanBePress = false;

	// 长按前的条件检查
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按条件", EditCondition = "bCanBePress", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionConditionBase>> PressConditions;

	// 长按时的效果
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按效果", EditCondition = "bCanBePress", EditConditionHides), Instanced)
	TArray<TObjectPtr<UInteractionOperatorBase>> PressOperators;

	// 长按可作用的地方
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "长按可作用的地方", EditCondition = "bCanBePress", EditConditionHides))
	TArray<EInteractionRoleType> PressRoleType;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TArray<TObjectPtr<UInteractionAbilityInfo>> TestAbilityInfos;

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInteractionAbilityInfo>> AbilityInfos;
};
