// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemStatics.generated.h"

UCLASS()
class SIDESCROLLER_API UAbilitySystemStatics : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static FGameplayEffectSpecHandle GetGameplayEffectSpecHandle(class USideScrollerGameplayAbility* OwningAbility);

    static void SetGameplayEffect(class UGameplayAbility* OwningAbility, AActor* ActorWithGameplayEffect);

    // Works only if the Instancing policy is set to instance-per-actor
    static UGameplayAbility* GetInstancedAbility(class UAbilitySystemComponent* AbilitySystem,
                                                 class UGameplayAbility* InAbility, int32 Level);
};
