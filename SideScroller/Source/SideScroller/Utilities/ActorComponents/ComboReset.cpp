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
