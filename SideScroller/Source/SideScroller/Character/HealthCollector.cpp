// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthCollector.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UHealthCollector::UHealthCollector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthCollector::BeginPlay()
{
	Super::BeginPlay();

	USideScrollerDelegates::OnCollectableHealthAdded.AddUObject(this, &UHealthCollector::ReceiveOnCollectableHealthAdded);
}

// Called every frame
void UHealthCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthCollector::ReceiveOnCollectableHealthAdded(int32 Amount)
{
	USideScrollerDelegates::OnPlayerAddHealth.Broadcast(Amount);
}
