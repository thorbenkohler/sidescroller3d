// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerHud.h"
#include "Utilities/SideScrollerDelegates.h"


bool USideScrollerHud::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}
	USideScrollerDelegates::OnPlayerChangeCoins.AddUObject(this, &USideScrollerHud::ReceiveOnPlayerChangeCoins);
	USideScrollerDelegates::OnPlayerChangeHealth.AddUObject(this, &USideScrollerHud::ReceiveOnPlayerChangeHealth);
	InitWidget();
	return true;
}

void USideScrollerHud::ReceiveOnPlayerChangeCoins(int32 Amount)
{
	CoinAmount = Amount;
}

void USideScrollerHud::ReceiveOnPlayerChangeHealth(int32 Amount)
{
	HealthAmount = Amount;
}
