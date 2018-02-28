// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableWeapon.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values
UCollectableWeapon::UCollectableWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UCollectableWeapon::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UCollectableWeapon::OnOverlap);
}

// Called every frame
void UCollectableWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollectableWeapon::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	USideScrollerDelegates::OnCollectableWeaponAdded.Broadcast(ReferencedCollectable);
	GetOwner()->Destroy();
}
