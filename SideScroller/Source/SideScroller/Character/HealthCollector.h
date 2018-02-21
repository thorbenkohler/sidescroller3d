// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collector.h"
#include "HealthCollector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLER_API UHealthCollector : public UCollector
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthCollector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// To react to collisions with collectable health
	void ReceiveOnCollectableHealthAdded(int32 Amount);
};
