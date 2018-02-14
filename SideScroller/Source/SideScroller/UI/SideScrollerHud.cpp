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
	USideScrollerDelegates::OnCollectableCoinAdded.AddUObject(this, &USideScrollerHud::ReceiveOnCollectableCoinAdded);
	USideScrollerDelegates::OnPlayerDamageReceived.AddUObject(this, &USideScrollerHud::ReceiveOnPlayerDamageReceived);
	return true;
}

void USideScrollerHud::ReceiveOnCollectableCoinAdded(int32 Amount)
{
	CoinAmount += Amount;
	UE_LOG(LogTemp, Log, TEXT("%d were added and result is now %d to %p"), Amount, CoinAmount, this);
}

void USideScrollerHud::ReceiveOnPlayerDamageReceived(int32 Amount)
{
	HealthAmount -= Amount;
	UE_LOG(LogTemp, Log, TEXT("%d damage done to player. Remaining Health %d"), Amount, HealthAmount);
}