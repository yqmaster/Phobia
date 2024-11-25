#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterComponent.h"
#include "PawnMoveComponent.generated.h"

UENUM(BlueprintType)
enum class EStrengthStateType : uint8
{
	IsFull UMETA(DisplayName = "已满"),
	OnUsing UMETA(DisplayName = "使用中"),
	RecoveringCanUse UMETA(DisplayName = "恢复中并可使用"),
	RecoveringNoUse UMETA(DisplayName = "恢复中不可使用"),
};

UCLASS(Blueprintable, abstract, ClassGroup = (ControllerComponent))
class PHOBIA_API UPawnMoveComponent : public UCharacterComponent
{
	GENERATED_BODY()

public:
	UPawnMoveComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D MoveAxis);

	UFUNCTION(BlueprintCallable)
	void StartRush();

	UFUNCTION(BlueprintCallable)
	void EndRush();

private:
	void StartRushImp();
	void EndRushImp(const bool bEndByPlayer);
	void TickCost();
	void TickRecover();

public:
	// 冲刺的速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move)
	float HighMoveSpeed = 300.f;

	// 走路的速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move)
	float LowMoveSpeed = 150.f;

private:
	// 最大的体力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Strength, meta = (AllowPrivateAccess = "true"))
	float MaxStrength = 100.f;

	// 当前的体力
	UPROPERTY(Transient)
	float CurStrength = 100.f;

	// 体力的消耗速度 多少每秒
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Strength, meta = (AllowPrivateAccess = "true"))
	float StrengthCostSpeed = 25.f;

	// 体力的恢复速度 多少每秒
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Strength, meta = (AllowPrivateAccess = "true"))
	float StrengthRecoverSpeed = 50.f;

	// Tick 间隔
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Strength, meta = (AllowPrivateAccess = "true"))
	float TickInterval = 0.03f;

	// 当前体力状态
	UPROPERTY(Transient)
	EStrengthStateType StrengthState = EStrengthStateType::IsFull;

	FTimerHandle TimerHandle;
};
