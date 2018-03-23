// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinCollector.h"
#include "UI/HighScoreWidget.h"
#include "SideScroller.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UCoinCollector::UCoinCollector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCoinCollector::BeginPlay()
{
	Super::BeginPlay();

	USideScrollerDelegates::OnCollectableCoinAdded.AddUObject(this, &UCoinCollector::ReceiveOnCollectableCoinAdded);
}

// Called every frame
void UCoinCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCoinCollector::ReceiveOnCollectableCoinAdded(int32 Amount)
{
	Coins += Amount;
	USideScrollerDelegates::OnPlayerChangeCoins.Broadcast(Coins);
	UE_LOG(SideScrollerLog, Log, TEXT("Collectable Coins %d added to %s"), Amount, *GetName());
}
