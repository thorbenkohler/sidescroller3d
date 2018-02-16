// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collector.h"
#include "Components/ActorComponent.h"
#include "CoinCollector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLER_API UCoinCollector : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoinCollector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// To react to collisions with collectable coins
	virtual void ReceiveOnCollectableCoinAdded(int32 Amount);

	virtual void ReceiveOnPlayerDied();

	virtual void ReceiveOnGameWon();
	
	// Current amount of coins
	int32 Amount;
};
