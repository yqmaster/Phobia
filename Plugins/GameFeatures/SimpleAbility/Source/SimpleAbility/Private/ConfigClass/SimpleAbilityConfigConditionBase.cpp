#include "ConfigClass/SimpleAbilityConfigConditionBase.h"

bool USimpleAbilityConfigConditionBase::CheckCondition(AActor* InCauser) const
{
	return ConditionCheck(GetOwnerActor(), InCauser) && ReceiveConditionCheck(GetOwnerActor(), InCauser);
}

bool USimpleAbilityConfigConditionBase::ReceiveConditionCheck_Implementation(AActor* InOwner, AActor* InCauser) const
{
	return true;
}

bool USimpleAbilityConfigConditionBase::ConditionCheck(AActor* InOwner, AActor* InCauser) const
{
	return true;
}

FString USimpleAbilityConfigConditionBase::GetConfigCategory() const
{
	return TEXT("Condition");
}

void USimpleAbilityConfigConditionBase::InitConfig(AActor* InOwner, USimpleAbilitySkill* InOwnerAbilitySkill)
{
	Super::InitConfig(InOwner, InOwnerAbilitySkill);
	InitCondition(InOwner);
	ReceiveInitCondition(InOwner);
}

void USimpleAbilityConfigConditionBase::UnInitConfig(AActor* InOwner)
{
	ReceiveUnInitCondition(InOwner);
	UnInitCondition(InOwner);
	Super::UnInitConfig(InOwner);
}
