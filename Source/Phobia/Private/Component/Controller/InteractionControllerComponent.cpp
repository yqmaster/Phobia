#include "Component/Controller/InteractionControllerComponent.h"

#include "EnhancedInputComponent.h"
#include "Component/Interaction/InteractionPlayerComponent.h"
#include "Component/Interaction/InteractionTypeDefine.h"
#include "GameFramework/Character.h"

void UInteractionControllerComponent::OnSetupInputComponent(UEnhancedInputComponent* InInputComponent)
{
	Super::OnSetupInputComponent(InInputComponent);

	BindKey(InInputComponent, EInteractionRoleType::Scene, LeftMouseAction);
	BindKey(InInputComponent, EInteractionRoleType::Hand, RightMouseAction);
	BindKey(InInputComponent, EInteractionRoleType::Pick, PickAction);
	BindKey(InInputComponent, EInteractionRoleType::Drop, DropAction);
	BindKey(InInputComponent, EInteractionRoleType::Put, PutAction);
}

void UInteractionControllerComponent::OnPossessed(ACharacter* InCharacter)
{
	Super::OnPossessed(InCharacter);

	// 缓存 InteractionComponent
	CacheInteractionComponent();
}

void UInteractionControllerComponent::OnUnPossessed()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TMap<EInteractionRoleType, FStartPressKeyInfo> TempPressKeyMap = PressKeyMap;
	for (auto& Pair : TempPressKeyMap)
	{
		TimerManager.ClearTimer(Pair.Value.TimerHandle);
		EndPressKey(Pair.Key);
	}
	TempPressKeyMap.Empty();
	PressKeyMap.Empty();

	// 清理 InteractionComponent
	UnCacheInteractionComponent();

	Super::OnUnPossessed();
}

void UInteractionControllerComponent::BindKey(UEnhancedInputComponent* InInputComponent, const EInteractionRoleType InRole, const UInputAction* InAction)
{
	InInputComponent->BindActionValueLambda(InAction, ETriggerEvent::Started, [this, InRole](const FInputActionValue& Value)
	{
		StartPressKey(InRole);
	});

	InInputComponent->BindActionValueLambda(InAction, ETriggerEvent::Completed, [this, InRole](const FInputActionValue& Value)
	{
		EndPressKey(InRole);
	});
}

void UInteractionControllerComponent::CacheInteractionComponent()
{
	const ACharacter* Character = GetControlledCharacter();
	if (!Character)
	{
		ensureAlwaysMsgf(false, TEXT("GetControlledCharacter for [%s] at [%s] failed, Character is nullptr"), *GetName(), *GetOwner()->GetName());
		return;
	}

	InteractionPlayerComponent = Character->GetComponentByClass<UInteractionPlayerComponent>();
}

void UInteractionControllerComponent::UnCacheInteractionComponent()
{
	InteractionPlayerComponent = nullptr;
}

void UInteractionControllerComponent::StartPressKey(const EInteractionRoleType InRole)
{
	UE_LOG(LogTemp, Log, TEXT("Start press key at role [%d]"), static_cast<uint8>(InRole));
	if (InteractionPlayerComponent && !PressKeyMap.Find(InRole))
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this, InRole]() { OnTimeOut(InRole); });
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, ShortPressTime, false);

		FStartPressKeyInfo PressKeyInfo;
		PressKeyInfo.TimerHandle = TimerHandle;
		PressKeyMap.Add(InRole, PressKeyInfo);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionPlayerComponent is nullptr or PressKeyMap has already had the key [%d] when StartPressKey"), static_cast<uint8>(InRole));
	}
}

void UInteractionControllerComponent::EndPressKey(const EInteractionRoleType InRole)
{
	UE_LOG(LogTemp, Log, TEXT("End press key at role [%d]"), static_cast<uint8>(InRole));
	if (InteractionPlayerComponent && PressKeyMap.Find(InRole))
	{
		FStartPressKeyInfo PressInfo = *PressKeyMap.Find(InRole);
		PressKeyMap.Remove(InRole);

		// 清理 Timer
		GetWorld()->GetTimerManager().ClearTimer(PressInfo.TimerHandle);

		if (PressInfo.bIsFire)
		{
			// 已经触发了证明是长按
			InteractionPlayerComponent->TriggerInteractionByPress(InRole, false);
		}
		else
		{
			// 未触发证明是点击
			InteractionPlayerComponent->TriggerInteractionByClick(InRole);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionPlayerComponent is nullptr or PressKeyMap not find the key [%d] when EndPressKey"), static_cast<uint8>(InRole));
	}
}

void UInteractionControllerComponent::OnTimeOut(const EInteractionRoleType InRole)
{
	if (InteractionPlayerComponent && PressKeyMap.Find(InRole))
	{
		FStartPressKeyInfo& PressInfo = *PressKeyMap.Find(InRole);

		// 清理 Timer
		GetWorld()->GetTimerManager().ClearTimer(PressInfo.TimerHandle);

		// 触发了这个函数证明是长按
		PressInfo.bIsFire = true;

		// 事件到了还没开始证明是长按事件
		InteractionPlayerComponent->TriggerInteractionByPress(InRole, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionPlayerComponent is nullptr or PressKeyMap not find the key [%d] when OnTimeOut"), static_cast<uint8>(InRole));
	}
}
