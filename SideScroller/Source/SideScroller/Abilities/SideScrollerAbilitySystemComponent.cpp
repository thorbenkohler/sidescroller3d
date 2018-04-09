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

void USideScrollerAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbiliyInputBinds BindInfo, EInputEvent InputEvent)
{
	UEnum* EnumBinds = BindInfo.GetBindEnum();

	SetBlockAbilityBindingsArray(BindInfo);

	for(int32 idx=0; idx < EnumBinds->NumEnums(); ++idx)
	{
		const FString FullStr = EnumBinds->GetNameStringByIndex(idx);
		
		// Pressed event
		{
			FInputActionBinding AB(FName(*FullStr), InputEvent);
			AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::AbilityLocalInputPressed, idx);
			InputComponent->AddActionBinding(AB);
		}

		// Released event
		{
			FInputActionBinding AB(FName(*FullStr), IE_Released);
			AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::AbilityLocalInputReleased, idx);
			InputComponent->AddActionBinding(AB);
		}
	}

	// Bind Confirm/Cancel. Note: these have to come last!
	if (BindInfo.ConfirmTargetCommand.IsEmpty() == false)
	{
		FInputActionBinding AB(FName(*BindInfo.ConfirmTargetCommand), InputEvent);
		AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::LocalInputConfirm);
		InputComponent->AddActionBinding(AB);
	}
	
	if (BindInfo.CancelTargetCommand.IsEmpty() == false)
	{
		FInputActionBinding AB(FName(*BindInfo.CancelTargetCommand), InputEvent);
		AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::LocalInputCancel);
		InputComponent->AddActionBinding(AB);
	}

	if (BindInfo.CancelTargetInputID >= 0)
	{
		GenericCancelInputID = BindInfo.CancelTargetInputID;
	}
	if (BindInfo.ConfirmTargetInputID >= 0)
	{
		GenericConfirmInputID = BindInfo.ConfirmTargetInputID;
	}
}
