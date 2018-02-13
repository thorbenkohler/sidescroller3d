// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSpawner.h"
#include "Weapons/Weapon.h"
#include "Enemies/Enemy.h"
#include "Character/SideScrollerCharacter.h"
#include "Projectiles/Projectile.h"
#include "Utilities/SideScrollerDelegates.h"
#include <Engine/World.h>


// Sets default values for this component's properties
UWeaponSpawner::UWeaponSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UWeaponSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UWeaponSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UWeaponSpawner::Spawn(TSubclassOf<AActor> ReferencedClass)
{
	FActorSpawnParameters SpawnParameters;
	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(ReferencedClass, SpawnParameters);
	if (!Weapon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Spawning Weapon failed"));
		return;
	}

	FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, false);
	AActor* Owner = GetOwner();
	Weapon->AttachToActor(Owner, Rules);
	Weapon->OwningActor = Owner;
	ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);
	if (SideScrollerCharacter->IsValidLowLevel())
	{
		Weapon->SideScrollerCharacter = SideScrollerCharacter;
	}
	Weapon->SetActorRelativeLocation(Weapon->Offset);

	UE_LOG(LogTemp, Log, TEXT("Weapon %s spawned"), *(Weapon->GetName()));
}