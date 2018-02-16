// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinCollector.h"
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
	USideScrollerDelegates::OnPlayerDied.AddUObject(this, &UCoinCollector::ReceiveOnPlayerDied);
}


// Called every frame
void UCoinCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UCoinCollector::ReceiveOnCollectableCoinAdded(int32 AddedAmount)
{
	Amount += AddedAmount;
	UE_LOG(LogTemp, Log, TEXT("Collectable Coins %d added to %s"), AddedAmount, *GetName());
}

void UCoinCollector::ReceiveOnPlayerDied()
{
	USideScrollerDelegates::OnShowHighscore.Broadcast(Amount);
}
