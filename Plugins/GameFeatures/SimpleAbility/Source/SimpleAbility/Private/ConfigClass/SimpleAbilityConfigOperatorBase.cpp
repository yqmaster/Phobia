#include "ConfigClass/SimpleAbilityConfigOperatorBase.h"

void USimpleAbilityConfigOperatorBase::StartDoOperator(AActor* InCauser)
{
	DoOperatorBegin(GetOwnerActor(), InCauser);
	ReceiveDoOperatorBegin(GetOwnerActor(), InCauser);
}

void USimpleAbilityConfigOperatorBase::EndDoOperator(AActor* InCauser)
{
	ReceiveDoOperatorEnd(GetOwnerActor(), InCauser);
	DoOperatorEnd(GetOwnerActor(), InCauser);
}

FString USimpleAbilityConfigOperatorBase::GetConfigCategory() const
{
	return TEXT("Operator");
}

void USimpleAbilityConfigOperatorBase::InitConfig(AActor* InOwnerActor, USimpleAbilitySkill* InOwnerAbilitySkill)
{
	Super::InitConfig(InOwnerActor, InOwnerAbilitySkill);
	InitOperator(InOwnerActor);
	ReceiveInitOperator(InOwnerActor);
}

void USimpleAbilityConfigOperatorBase::UnInitConfig(AActor* InOwnerActor)
{
	ReceiveUnInitOperator(InOwnerActor);
	UnInitOperator(InOwnerActor);
	Super::UnInitConfig(InOwnerActor);
}
