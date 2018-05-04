// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameplayEffectInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameplayEffectInterface : public UInterface
{
    GENERATED_BODY()
};

class SIDESCROLLER_API IGameplayEffectInterface
{
    GENERATED_BODY()

public:
    virtual void SetGameplayEffect(FGameplayEffectSpecHandle GameplayEffectSpecHandle) = 0;

    virtual FGameplayEffectSpecHandle GetGameplayEffect() const = 0;
};
