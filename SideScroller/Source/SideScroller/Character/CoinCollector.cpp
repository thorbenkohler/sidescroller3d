// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinCollector.h"
#include "SideScroller.h"
#include "Utilities/SideScrollerDelegates.h"

// Called when the game starts
void UCoinCollector::BeginPlay()
{
    Super::BeginPlay();

    USideScrollerDelegates::OnCollectableCoinAdded.AddUObject(this, &UCoinCollector::ReceiveOnCollectableCoinAdded);
}

void UCoinCollector::ReceiveOnCollectableCoinAdded(int32 Amount)
{
    Coins += Amount;
    USideScrollerDelegates::OnPlayerChangeCoins.Broadcast(Coins);
    UE_LOG(SideScrollerLog, Log, TEXT("Collectable Coins %d added to %s"), Amount, *GetName());
}
