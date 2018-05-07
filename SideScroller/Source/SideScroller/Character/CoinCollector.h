// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Collector.h"
#include "CoinCollector.generated.h"


UCLASS()
class SIDESCROLLER_API UCoinCollector : public UCollector
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// To react to collisions with collectable coins
	void ReceiveOnCollectableCoinAdded(int32 Amount);

	// Current amount of coins
	int32 Coins;
};
