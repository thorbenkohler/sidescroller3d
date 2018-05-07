// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystemStatics.h"
#include "Interfaces/GameplayEffectInterface.h"
#include "Abilities/SideScrollerGameplayAbility.h"

FGameplayEffectSpecHandle
UAbilitySystemStatics::GetGameplayEffectSpecHandle(USideScrollerGameplayAbility* OwningAbility)
{
    FGameplayAbilitySpecHandle Handle = OwningAbility->GetCurrentAbilitySpecHandle();
    FGameplayAbilityActorInfo TempActorInfo = OwningAbility->GetActorInfo();
    FGameplayAbilityActorInfo* ActorInfo = &TempActorInfo;
    FGameplayAbilityActivationInfo ActivationInfo = OwningAbility->GetCurrentActivationInfo();

    TSubclassOf<UGameplayEffect> ImpactGameplayEffect = OwningAbility->ImpactGameplayEffect;

    // Construct an impact game play effect spec and pass it to the projectile.
    FGameplayEffectSpecHandle SpecHandle = OwningAbility->MakeOutgoingGameplayEffectSpec(
        Handle, ActorInfo, ActivationInfo, ImpactGameplayEffect, OwningAbility->GetAbilityLevel(Handle, ActorInfo));

    return SpecHandle;
}

void UAbilitySystemStatics::SetGameplayEffect(UGameplayAbility* OwningAbility, AActor* ActorWithGameplayEffect)
{
    USideScrollerGameplayAbility* SideScrollerGameplayAbility = Cast<USideScrollerGameplayAbility>(OwningAbility);

    if (!IsValid(SideScrollerGameplayAbility))
    {
        UE_LOG(SideScrollerLog, Warning, TEXT("%s OwningAbility %s is not of type USideScrollerGameplayAbility"),
               *LOG_STACK, *OwningAbility->GetName());
        return;
    }

    FGameplayEffectSpecHandle GameplayEffectSpecHandle =
        UAbilitySystemStatics::GetGameplayEffectSpecHandle(SideScrollerGameplayAbility);

    IGameplayEffectInterface* GameplayEffectInterface = Cast<IGameplayEffectInterface>(ActorWithGameplayEffect);

    if (!GameplayEffectInterface)
    {
        UE_LOG(SideScrollerLog, Warning,
               TEXT("%s SpawnedActor \"%s\" is not of type IGameplayEffectInterface. GameplayEffect won't be "
                    "applied."),
               *LOG_STACK, *ActorWithGameplayEffect->GetName());
        return;
    }

    GameplayEffectInterface->SetGameplayEffect(GameplayEffectSpecHandle);
}

UGameplayAbility* UAbilitySystemStatics::GetInstancedAbility(UAbilitySystemComponent* AbilitySystem,
                                                             UGameplayAbility* InAbility, int32 Level)
{
    FGameplayAbilitySpec GameplayAbilitySpec(InAbility, Level);
    FGameplayAbilitySpecHandle GameplayAbilitySpecHandle = AbilitySystem->GiveAbility(GameplayAbilitySpec);

    for (FGameplayAbilitySpec TempGameplayAbilitySpec : AbilitySystem->GetActivatableAbilities())
    {
        TArray<UGameplayAbility*> InstancedAbilities = TempGameplayAbilitySpec.GetAbilityInstances();
        for (UGameplayAbility* TempInstancedAbility : InstancedAbilities)
        {
            if (!IsValid(TempInstancedAbility))
            {
                UE_LOG(SideScrollerLog, Error, TEXT("InstancedAbility is not valid"));
                continue;
            }

            return TempInstancedAbility;
        }
    }

    UE_LOG(SideScrollerLog, Error, TEXT("%s No instanced ability could be found."), *LOG_STACK);
    return nullptr;
}
