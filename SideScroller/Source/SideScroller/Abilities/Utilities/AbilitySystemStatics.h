// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Abilities/SideScrollerGameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemStatics.generated.h"

/**
*
*/
UCLASS()
class SIDESCROLLER_API UAbilitySystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static FGameplayEffectSpecHandle GetGameplayEffectSpecHandle(USideScrollerGameplayAbility* OwningAbility);

	static void SetGameplayEffect(UGameplayAbility* OwningAbility, AActor* ActorWithGameplayEffect);

	static UGameplayAbility* GetInstancedAbility(UAbilitySystemComponent* AbilitySystem, UGameplayAbility* InAbility, int32 Level);
};
