// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponCollector.h"
#include "Weapons/Weapon.h"
#include "Weapons/RangedWeapon.h"
#include "Weapons/MeleeWeapon.h"
#include "Weapons/WeaponSpawner.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UWeaponCollector::UWeaponCollector()
{
	WeaponSpawner = CreateDefaultSubobject<UWeaponSpawner>(TEXT("WeaponSpawner"));
}

// Called when the game starts
void UWeaponCollector::BeginPlay()
{
	Super::BeginPlay();

	USideScrollerDelegates::OnCollectableWeaponAdded.AddUObject(this, &UWeaponCollector::ReceiveOnCollectableWeaponAdded);
}

void UWeaponCollector::ReceiveOnCollectableWeaponAdded(TSubclassOf<AActor> WeaponReference)
{
	if (!IsValid(WeaponSpawner))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("WeaponSpawner is not valid."));
		return;
	}

	AWeapon* SpawnedWeapon = WeaponSpawner->Spawn(WeaponReference);

	if (!IsValid(SpawnedWeapon))
	{
		UE_LOG(SideScrollerLog, Log, TEXT("Spawning weapon failed."));
		return;
	}

	ARangedWeapon* RangedWeapon = Cast<ARangedWeapon>(SpawnedWeapon);
	
	if (IsValid(RangedWeapon))
	{
		CurrentlyEquippedRangedWeapon = RangedWeapon;
	}

	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(SpawnedWeapon);

	if (IsValid(MeleeWeapon))
	{
		CurrentlyEquippedMeleeWeapon = MeleeWeapon;
	}

	OnWeaponCollected.Broadcast(SpawnedWeapon);
}
