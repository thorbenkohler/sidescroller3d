// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSpawner.h"
#include "Weapons/Weapon.h"
#include "Weapons/PlayerWeapon.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"


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

	if (!IsValid(Weapon))
	{
		UE_LOG(LogTemp, Error, TEXT("Spawning Weapon failed"));
		return;
	}

	FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, false);
	AActor* Owner = GetOwner();
	Weapon->AttachToActor(Owner, Rules);
	Weapon->SetActorRelativeLocation(Weapon->Offset);
	FRotator OwnerRotation = Owner->GetActorRotation();

	// If the weapon owner is rotated against the standard direction, adjust the weapon direction
	if (OwnerRotation.Yaw > 0.0f)
	{
		FRotator NewRotation = Weapon->GetActorRotation();
		NewRotation.Yaw = -90.0f;
		Weapon->SetActorRelativeRotation(NewRotation);
	}
	Weapon->WeaponOwner = Owner;

	APlayerWeapon* PlayerWeapon = Cast<APlayerWeapon>(Weapon);

	if (!IsValid(PlayerWeapon))
	{
		return;
	}

	ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

	if (!IsValid(SideScrollerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("Player Weapon %s without a valid owner was spawned."), *PlayerWeapon->GetName());
		return;
	}

	PlayerWeapon->SideScrollerCharacter = SideScrollerCharacter;
}