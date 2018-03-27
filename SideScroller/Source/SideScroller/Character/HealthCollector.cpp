// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthCollector.h"
#include "Utilities/SideScrollerDelegates.h"

// Called when the game starts
void UHealthCollector::BeginPlay()
{
    Super::BeginPlay();

    USideScrollerDelegates::OnCollectableHealthAdded.AddUObject(this,
                                                                &UHealthCollector::ReceiveOnCollectableHealthAdded);
}

void UHealthCollector::ReceiveOnCollectableHealthAdded(int32 Amount)
{
    USideScrollerDelegates::OnPlayerAddHealth.Broadcast(Amount);
}
