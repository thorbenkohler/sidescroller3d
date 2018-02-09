// Fill out your copyright notice in the Description page of Project Settings.

#include "Collector.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UCollector::UCollector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCollector::BeginPlay()
{
	Super::BeginPlay();

	USideScrollerDelegates::OnCollectableAdded.AddUObject(this, &UCollector::ReceiveOnCollectableAdded);
}


// Called every frame
void UCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollector::ReceiveOnCollectableAdded(ACollectable* Collectable)
{
	UE_LOG(LogTemp, Log, TEXT("Collectable %s collected"), *(Collectable->GetName()));
}
