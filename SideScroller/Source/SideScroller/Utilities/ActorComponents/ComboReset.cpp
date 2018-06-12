// Fill out your copyright notice in the Description page of Project Settings.

#include "ComboReset.h"
#include "Utilities/SideScrollerDelegates.h"

UComboReset::UComboReset()
{
    USideScrollerDelegates::OnCharacterLanded.AddUObject(this, &UComboReset::ReceiveOnCharacterLanded);
}

void UComboReset::ReceiveOnCharacterLanded(const FHitResult& Hit)
{
    Reset();
}

void UComboReset::Reset_Implementation()
{
    USideScrollerDelegates::OnResetCombo.Broadcast();
}

UActorComponent* UComboReset::GetResettableComponent()
{
    AActor* Owner = GetOwner();

    if (!IsValid(Owner))
    {
        return nullptr;
    }

    TSet<UActorComponent*> Components = Owner->GetComponents();

    for (UActorComponent* Component : Components)
    {
        IComboResettable* ComboResettable = Cast<IComboResettable>(Component);
        if (ComboResettable)
        {
            return Component;
        }
    }

    UE_LOG(SideScrollerLog, Error, TEXT("%s ComboResettable at owner %s not found."), *LOG_STACK, *GetOwner()->GetName());
    return nullptr;
}