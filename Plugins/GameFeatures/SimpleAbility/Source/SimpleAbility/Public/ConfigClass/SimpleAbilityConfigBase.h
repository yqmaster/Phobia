#pragma once

#include "CoreMinimal.h"
#include "SimpleAbilityConfigBase.generated.h"

class USimpleAbilitySkill;

/**
 * 
 */
UCLASS(BlueprintType, Abstract, ClassGroup = (SimpleAbility))
class SIMPLEABILITY_API USimpleAbilityConfigBase : public UObject
{
	GENERATED_BODY()

public:
	// 外部调用: 初始化配置
	virtual void InitConfig(AActor* InOwnerActor, USimpleAbilitySkill* InOwnerAbilitySkill);

	// 外部调用: 反初始化配置
	virtual void UnInitConfig(AActor* InOwnerActor);

	// 外部调用: 设置配置索引
	void SetConfigIndex(const int32 InConfigIndex);

protected:
	// 内部使用: 获取 AbilitySkill, 用于子类调用
	USimpleAbilitySkill* GetOwnerAbilitySkill() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SimpleAbility")
	AActor* GetOwnerActor() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SimpleAbility")
	int32 GetConfigIndex() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SimpleAbility")
	virtual FString GetConfigCategory() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SimpleAbility")
	FString GetConfigInfo() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<USimpleAbilitySkill> OwnerAbilitySkill;

	UPROPERTY(Transient)
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(Transient)
	int32 ConfigIndex = INDEX_NONE;
};
