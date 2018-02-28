// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableCoin.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values
UCollectableCoin::UCollectableCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UCollectableCoin::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UCollectableCoin::OnOverlap);
}

// Called every frame
void UCollectableCoin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollectableCoin::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	USideScrollerDelegates::OnCollectableCoinAdded.Broadcast(Amount);
	GetOwner()->Destroy();
}
