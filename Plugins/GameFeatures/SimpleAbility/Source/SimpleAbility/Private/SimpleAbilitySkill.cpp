#include "SimpleAbilitySkill.h"

#include "ConfigClass/SimpleAbilityConfigEventBase.h"
#include "ConfigClass/SimpleAbilityConfigConditionBase.h"
#include "ConfigClass/SimpleAbilityConfigOperatorBase.h"

DEFINE_LOG_CATEGORY(SimpleAbility);

USimpleAbilitySkill* USimpleAbilitySkill::CreateSkill(const USimpleAbilityConfigEventBase* InEvent, const TArray<USimpleAbilityConfigConditionBase*>& InConditions, const TArray<USimpleAbilityConfigOperatorBase*>& InOperators, AActor* InOwnerActor, FString& InSkillName)
{
	// 检查拥有者是否为空
	if (InOwnerActor == nullptr)
	{
		UE_LOG(SimpleAbility, Error, TEXT("CreateAbilitySkill [%s] Failed, OwnerActor is nullptr"), *InSkillName);
		return nullptr;
	}

	// 检查事件是否为空
	if (InEvent == nullptr)
	{
		UE_LOG(SimpleAbility, Error, TEXT("CreateAbilitySkill [%s] For [%s] Failed, Event is nullptr"), *InSkillName, *InOwnerActor->GetName());
		return nullptr;
	}

	USimpleAbilitySkill* NewAbilitySkill = NewObject<USimpleAbilitySkill>();
	NewAbilitySkill->Event = DuplicateConfig(InEvent);
	NewAbilitySkill->Conditions = DuplicateConfigArray(InConditions);
	NewAbilitySkill->Operators = DuplicateConfigArray(InOperators);
	NewAbilitySkill->OwnerActor = InOwnerActor;
	NewAbilitySkill->AbilitySkillName = InSkillName;

	// 检查操作是否为空，为空则警告
	if (NewAbilitySkill->Operators.Num() <= 0)
	{
		UE_LOG(SimpleAbility, Warning, TEXT("CreateAbilitySkill [%s] For [%s], But Operators is empty"), *InSkillName, *InOwnerActor->GetName());
	}

	NewAbilitySkill->InitConfigs();
	return NewAbilitySkill;
}

void USimpleAbilitySkill::ActiveSkill(const USimpleAbilitySkill* InAbilitySkill)
{
	InAbilitySkill->ActiveAbilitySkill();
}

void USimpleAbilitySkill::DestroySkill(USimpleAbilitySkill* InAbilitySkill)
{
	InAbilitySkill->DeActiveAbilitySkill();
	InAbilitySkill->UnInitConfigs();
}

void USimpleAbilitySkill::TriggerEventStart(AActor* InCauserActor)
{
	UE_LOG(SimpleAbility, Log, TEXT("TriggerSkillStart [%s] for [%s] by [%s]"), *AbilitySkillName, *OwnerActor->GetName(), *InCauserActor->GetName());

	// 条件检查
	for (const USimpleAbilityConfigConditionBase* Condition : Conditions)
	{
		if (!Condition->CheckCondition(InCauserActor))
		{
			UE_LOG(SimpleAbility, Log, TEXT("CheckSkill [%s] Condition [%s] for [%s] by [%s]"), *AbilitySkillName, *Condition->GetName(), *OwnerActor->GetName(), *InCauserActor->GetName());
			return;
		}
	}

	UE_LOG(SimpleAbility, Log, TEXT("Skill [%s] start do operator for [%s] by [%s]"), *AbilitySkillName, *OwnerActor->GetName(), *InCauserActor->GetName());

	// 开始执行操作
	for (USimpleAbilityConfigOperatorBase* Operator : Operators)
	{
		Operator->StartDoOperator(InCauserActor);
	}
}

void USimpleAbilitySkill::TriggerEventEnd(AActor* InCauserActor)
{
	UE_LOG(SimpleAbility, Log, TEXT("Skill [%s] end do operator for [%s] by [%s]"), *AbilitySkillName, *OwnerActor->GetName(), *InCauserActor->GetName());

	// 结束执行操作
	for (USimpleAbilityConfigOperatorBase* Operator : Operators)
	{
		Operator->EndDoOperator(InCauserActor);
	}
}

FString USimpleAbilitySkill::GetSkillName() const
{
	return AbilitySkillName;
}

void USimpleAbilitySkill::InitConfigs()
{
	UE_LOG(SimpleAbility, Log, TEXT("InitSkill [%s] for [%s]"), *AbilitySkillName, *OwnerActor->GetName());
	TArray<TObjectPtr<USimpleAbilityConfigBase>> Configs;
	Configs.Add(Event);
	Configs.Append(Conditions);
	Configs.Append(Operators);

	for (const TObjectPtr<USimpleAbilityConfigBase> Config : Configs)
	{
		Config->InitConfig(OwnerActor, this);
	}
}

void USimpleAbilitySkill::UnInitConfigs()
{
	UE_LOG(SimpleAbility, Log, TEXT("UnInitSkill [%s] for [%s]"), *AbilitySkillName, *OwnerActor->GetName());
	TArray<TObjectPtr<USimpleAbilityConfigBase>> Configs;
	Configs.Add(Event);
	Configs.Append(Conditions);
	Configs.Append(Operators);

	for (const TObjectPtr<USimpleAbilityConfigBase> Config : Configs)
	{
		Config->UnInitConfig(OwnerActor);
	}

	Event = nullptr;
	Conditions.Empty();
	Operators.Empty();
}

void USimpleAbilitySkill::ActiveAbilitySkill() const
{
	UE_LOG(SimpleAbility, Log, TEXT("ActiveSkill [%s] for [%s]"), *AbilitySkillName, *OwnerActor->GetName());
	Event->ActiveEvent();
}

void USimpleAbilitySkill::DeActiveAbilitySkill() const
{
	UE_LOG(SimpleAbility, Log, TEXT("DeActiveSkill [%s] for [%s]"), *AbilitySkillName, *OwnerActor->GetName());
	Event->DeActiveEvent();
}
