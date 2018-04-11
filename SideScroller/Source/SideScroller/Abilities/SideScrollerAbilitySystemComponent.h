// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "SideScrollerAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API USideScrollerAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	FGameplayAbilitySpecHandle GiveAbility(const FGameplayAbilitySpec& AbilitySpec);
};
