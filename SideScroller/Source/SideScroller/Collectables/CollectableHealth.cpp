// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableHealth.h"
#include "Utilities/SideScrollerDelegates.h"


// Called when the game starts
void UCollectableHealth::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UCollectableHealth::OnOverlap);
}

void UCollectableHealth::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	USideScrollerDelegates::OnCollectableHealthAdded.Broadcast(Amount);
	GetOwner()->Destroy();
}
