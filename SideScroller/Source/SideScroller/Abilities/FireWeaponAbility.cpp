// Fill out your copyright notice in the Description page of Project Settings.

#include "FireWeaponAbility.h"
#include "Abilities/Utilities/AbilitySystemStatics.h"
#include "Abilities/Utilities/AbilityDelegates.h"

void UFireWeaponAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
        return;
    }

    OnActivated();
}

