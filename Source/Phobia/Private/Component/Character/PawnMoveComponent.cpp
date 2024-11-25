#include "Component/Character/PawnMoveComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPawnMoveComponent::UPawnMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPawnMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovementComponent())
	{
		MovementComponent->MaxWalkSpeed = LowMoveSpeed;
	}

	CurStrength = MaxStrength;
	StrengthState = EStrengthStateType::IsFull;
}

void UPawnMoveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UPawnMoveComponent::Move(const FVector2D MoveAxis)
{
	if (ACharacter* Character = GetOwnerCharacter())
	{
		const FVector RightVector = Character->GetActorRightVector() * MoveAxis.X;
		const FVector ForwardVector = Character->GetActorForwardVector() * MoveAxis.Y;
		Character->AddMovementInput((RightVector + ForwardVector).GetSafeNormal());
	}
}

void UPawnMoveComponent::StartRush()
{
	// 满了和可以缓慢恢复则可以使用
	if (StrengthState == EStrengthStateType::IsFull || StrengthState == EStrengthStateType::RecoveringCanUse)
	{
		StartRushImp();
		return;
	}

	// 不可使用则返回
	if (StrengthState == EStrengthStateType::RecoveringNoUse)
	{
		return;
	}

	// 不可能是 OnUsing
	if (StrengthState == EStrengthStateType::OnUsing)
	{
		UE_LOG(LogTemp, Error, TEXT("InValid EStrengthStateType::OnUsing"));
		return;
	}

	ensureAlways(false);
}

void UPawnMoveComponent::EndRush()
{
	// 冲刺中途的时候松手，为手动停止
	if (StrengthState == EStrengthStateType::OnUsing)
	{
		EndRushImp(true);
		return;
	}

	// 恢复且不可用，或者恢复满了的时候松手，忽略
	if (StrengthState == EStrengthStateType::RecoveringNoUse || StrengthState == EStrengthStateType::IsFull)
	{
		return;
	}

	// 不可能是 RecoveringCanUse
	if (StrengthState == EStrengthStateType::RecoveringCanUse)
	{
		UE_LOG(LogTemp, Error, TEXT("InValid EStrengthStateType::RecoveringCanUse"));
		return;
	}

	ensureAlways(false);
}

void UPawnMoveComponent::StartRushImp()
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovementComponent())
	{
		MovementComponent->MaxWalkSpeed = HighMoveSpeed;
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(TimerHandle);
	TimerManager.SetTimer(TimerHandle, this, &UPawnMoveComponent::TickCost, TickInterval, true);

	StrengthState = EStrengthStateType::OnUsing;
}

void UPawnMoveComponent::EndRushImp(const bool bEndByPlayer)
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovementComponent())
	{
		MovementComponent->MaxWalkSpeed = LowMoveSpeed;
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(TimerHandle);
	TimerManager.SetTimer(TimerHandle, this, &UPawnMoveComponent::TickRecover, TickInterval, true);

	StrengthState = bEndByPlayer ? EStrengthStateType::RecoveringCanUse : EStrengthStateType::RecoveringNoUse;
}

void UPawnMoveComponent::TickCost()
{
	ensureAlways(StrengthState == EStrengthStateType::OnUsing);
	CurStrength -= StrengthCostSpeed * TickInterval;

	if (CurStrength <= 0)
	{
		CurStrength = 0;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		EndRushImp(false);
		StrengthState = EStrengthStateType::RecoveringNoUse;
	}
}

void UPawnMoveComponent::TickRecover()
{
	ensureAlways(StrengthState == EStrengthStateType::RecoveringCanUse || StrengthState == EStrengthStateType::RecoveringNoUse);
	CurStrength += StrengthRecoverSpeed * TickInterval;

	if (CurStrength >= MaxStrength)
	{
		CurStrength = MaxStrength;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		StrengthState = EStrengthStateType::IsFull;
	}
}
