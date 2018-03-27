// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableWeapon.h"
#include "Utilities/SideScrollerDelegates.h"


// Called when the game starts or when spawned
void UCollectableWeapon::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UCollectableWeapon::OnOverlap);
}

void UCollectableWeapon::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	USideScrollerDelegates::OnCollectableWeaponAdded.Broadcast(ReferencedCollectable);
	GetOwner()->Destroy();
}
