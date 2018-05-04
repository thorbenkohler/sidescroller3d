// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "Interfaces/GameplayEffectInterface.h"
#include "SideScrollerGameplayAbility.generated.h"

UCLASS()
class SIDESCROLLER_API USideScrollerGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                 const FGameplayEventData* TriggerEventData) override;

    /** Gameplay effect to apply to the target. */
    UPROPERTY(Category = "SideScroller", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TSubclassOf<UGameplayEffect> ImpactGameplayEffect;

	IGameplayEffectInterface* CausingActor;
};
