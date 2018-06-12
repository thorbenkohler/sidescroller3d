// Fill out your copyright notice in the Description page of Project Settings.

#include "ComboReset.h"
#include "Utilities/SideScrollerDelegates.h"

UComboReset::UComboReset()
{
    USideScrollerDelegates::OnCharacterLanded.AddUObject(this, &UComboReset::ReceiveOnCharacterLanded);
}

void UComboReset::ReceiveOnCharacterLanded(const FHitResult& Hit)
{
    AActor* Owner = GetOwner();

    if (!IsValid(Owner))
    {
        return;
    }

    TSet<UActorComponent*> Components = Owner->GetComponents();

    for (UActorComponent* Component : Components)
    {
        IComboResettable* ComboResettable = Cast<IComboResettable>(Component);
        if (ComboResettable)
        {
            ComboResettable->ComboReset();
            break;
        }
    }
}
