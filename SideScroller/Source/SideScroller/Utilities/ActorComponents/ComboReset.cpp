// Fill out your copyright notice in the Description page of Project Settings.

#include "ComboReset.h"
#include "Utilities/SideScrollerDelegates.h"

UComboReset::UComboReset()
{
    USideScrollerDelegates::OnResetCombo.AddUObject(this, &UComboReset::Reset);
}

void UComboReset::Reset_Implementation(const FHitResult& Hit)
{

}
