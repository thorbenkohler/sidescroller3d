// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableCoin.h"
#include "Utilities/SideScrollerDelegates.h"


// Called when the game starts or when spawned
void UCollectableCoin::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UCollectableCoin::OnOverlap);
}

void UCollectableCoin::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	USideScrollerDelegates::OnCollectableCoinAdded.Broadcast(Amount);
	GetOwner()->Destroy();
}
