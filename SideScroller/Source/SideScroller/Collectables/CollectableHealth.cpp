// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableHealth.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UCollectableHealth::UCollectableHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCollectableHealth::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UCollectableHealth::OnOverlap);
}

// Called every frame
void UCollectableHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollectableHealth::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	USideScrollerDelegates::OnCollectableHealthAdded.Broadcast(Amount);
	GetOwner()->Destroy();
}
