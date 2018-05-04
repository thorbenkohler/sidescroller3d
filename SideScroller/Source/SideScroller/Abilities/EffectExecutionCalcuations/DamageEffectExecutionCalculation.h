// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerEffectExecutionCalculation.h"
#include "DamageEffectExecutionCalculation.generated.h"

UCLASS()
class SIDESCROLLER_API UDamageEffectExecutionCalculation : public USideScrollerEffectExecutionCalculation
{
	GENERATED_UCLASS_BODY()
	
public:
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                        OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
