// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSpawner.h"
#include "Weapons/Weapon.h"
#include "Weapons/PlayerWeapon.h"
#include "Character/SideScrollerCharacter.h"


AWeapon* UWeaponSpawner::Spawn(TSubclassOf<AActor> ReferencedClass)
{
	FActorSpawnParameters SpawnParameters;
	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(ReferencedClass, SpawnParameters);

	if (!IsValid(Weapon))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Spawning Weapon failed"));
		return nullptr;
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
	Weapon->BindDelegates();

	APlayerWeapon* PlayerWeapon = Cast<APlayerWeapon>(Weapon);

	if (!IsValid(PlayerWeapon))
	{
		return Weapon;
	}

	ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

	if (!IsValid(SideScrollerCharacter))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Player Weapon %s without a valid owner was spawned."), *PlayerWeapon->GetName());
		return Weapon;
	}

	TSubclassOf<class UGameplayAbility> Ability = PlayerWeapon->Ability;

	if (!IsValid(Ability))
	{
		UE_LOG(SideScrollerLog, Warning, TEXT("Player Weapon %s without a ability was collected."), *PlayerWeapon->GetName());
		return Weapon;
	}

	SideScrollerCharacter->AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, (uint32) AbilityInput::FireWeapon));

	return Weapon;
}