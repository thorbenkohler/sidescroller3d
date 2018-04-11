// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerAbilitySystemComponent.h"

FGameplayAbilitySpecHandle USideScrollerAbilitySystemComponent::GiveAbility(const FGameplayAbilitySpec& Spec)
{
    check(Spec.Ability);
    check(IsOwnerActorAuthoritative()); // Should be called on authority

    // If locked, add to pending list. The Spec.Handle is not regenerated when we receive, so returning this is ok.
    if (AbilityScopeLockCount > 0)
    {
        AbilityPendingAdds.Add(Spec);
        return Spec.Handle;
    }

    FGameplayAbilitySpec& OwnedSpec = ActivatableAbilities.Items[ActivatableAbilities.Items.Add(Spec)];

    if (OwnedSpec.Ability->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerActor)
    {
        // Create the instance at creation time
        CreateNewInstanceOfAbility(OwnedSpec, Spec.Ability);
    }

    OnGiveAbility(OwnedSpec);
    MarkAbilitySpecDirty(OwnedSpec);

    return OwnedSpec.Handle;
}
