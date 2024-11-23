// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

/**
 * @brief 可交互物体基类
 */
UCLASS(Blueprintable, abstract, ClassGroup = (ItemActor))
class PHOBIA_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
};
