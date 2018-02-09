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
	return true;
}

void USideScrollerHud::ReceiveOnCollectableCoinAdded(int32 Amount)
{
	CoinAmount += Amount;
	UE_LOG(LogTemp, Log, TEXT("%d were added and result is now %d to %p"), Amount, CoinAmount, this);
}
