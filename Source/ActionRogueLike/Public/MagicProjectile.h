// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectBase.h"
#include "MagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AMagicProjectile : public ASProjectBase
{
	GENERATED_BODY()
public:
	//构造，初始化子弹基本属性
	AMagicProjectile();

protected:
	virtual void BeginPlay() override;
};
