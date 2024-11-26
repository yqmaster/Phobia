#include "ConfigClass/SimpleAbilityConfigBase.h"

#include "SimpleAbilitySkill.h"

void USimpleAbilityConfigBase::InitConfig(AActor* InOwnerActor, USimpleAbilitySkill* InOwnerAbilitySkill)
{
	OwnerAbilitySkill = InOwnerAbilitySkill;
	OwnerActor = InOwnerActor;
}

void USimpleAbilityConfigBase::UnInitConfig(AActor* InOwnerActor)
{
	OwnerActor = nullptr;
	OwnerAbilitySkill = nullptr;
}

void USimpleAbilityConfigBase::SetConfigIndex(const int32 InConfigIndex)
{
	ConfigIndex = InConfigIndex;
}

USimpleAbilitySkill* USimpleAbilityConfigBase::GetOwnerAbilitySkill() const
{
	return OwnerAbilitySkill;
}

AActor* USimpleAbilityConfigBase::GetOwnerActor() const
{
	return OwnerActor;
}

int32 USimpleAbilityConfigBase::GetConfigIndex() const
{
	return ConfigIndex;
}

FString USimpleAbilityConfigBase::GetConfigCategory() const
{
	return TEXT("ConfigBase");
}

FString USimpleAbilityConfigBase::GetConfigInfo() const
{
	if (OwnerAbilitySkill && OwnerActor)
	{
		return FString::Printf(TEXT("SimpleAbility: Skill [%s], Owner [%s], Category [%s], Index [%d], Name [%s]"), *OwnerAbilitySkill->GetSkillName(), *GetOwnerActor()->GetName(), *GetConfigCategory(), ConfigIndex, *GetName());
	}

	return FString::Printf(TEXT("SimpleAbility: Category [%s], Index [%d]"), *GetConfigCategory(), ConfigIndex);
}
