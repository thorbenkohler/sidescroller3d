// Fill out your copyright notice in the Description page of Project Settings.

#include "DashAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Utilities/AbilitySystemStatics.h"
#include "Utilities/AbilityDelegates.h"

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                   const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    UAbilityDelegates::OnDashOverlapBegin.AddUObject(this, &UDashAbility::ReceiveOnDashBeginOverlap);
}

void UDashAbility::ReceiveOnDashBeginOverlap(AActor* HitTarget)
{
    UAbilitySystemComponent* AbilitySystemComponent =
        UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitTarget);
	
	FGameplayEffectSpecHandle ImpactEffect = UAbilitySystemStatics::GetGameplayEffectSpecHandle(this);

    if (IsValid(AbilitySystemComponent) && ImpactEffect.IsValid())
    {
        AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*ImpactEffect.Data.Get());
    }
}
