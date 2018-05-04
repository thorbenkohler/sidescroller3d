// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerGameplayAbility.h"
#include "DashAbility.generated.h"

UCLASS()
class SIDESCROLLER_API UDashAbility : public USideScrollerGameplayAbility
{
    GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                 const FGameplayEventData* TriggerEventData) override;


	void ReceiveOnDashBeginOverlap(AActor* HitTarget);
};
