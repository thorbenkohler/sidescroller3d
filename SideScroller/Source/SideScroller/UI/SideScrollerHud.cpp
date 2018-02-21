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
	USideScrollerDelegates::OnPlayerChangeHealth.AddUObject(this, &USideScrollerHud::ReceiveOnPlayerChangeHealth);
	InitWidget();
	return true;
}

void USideScrollerHud::ReceiveOnCollectableCoinAdded(int32 Amount)
{
	CoinAmount += Amount;
	UE_LOG(LogTemp, Log, TEXT("%d Coin were added and result is %d"), Amount, CoinAmount);
}

void USideScrollerHud::ReceiveOnPlayerChangeHealth(int32 Amount)
{
	HealthAmount = Amount;
	UE_LOG(LogTemp, Log, TEXT("%d Health of Player changed. Remaining Health %d"), Amount, HealthAmount);
}
