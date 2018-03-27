// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Collector.h"
#include "HealthCollector.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDESCROLLER_API UHealthCollector : public UCollector
{
    GENERATED_BODY()

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // To react to collisions with collectable health
    void ReceiveOnCollectableHealthAdded(int32 Amount);
};
