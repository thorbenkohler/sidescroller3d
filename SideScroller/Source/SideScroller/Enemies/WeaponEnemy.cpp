// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponEnemy.h"
#include "Abilities/FireWeaponAbility.h"
#include "GameplayAbilitySpec.h"


AWeaponEnemy::AWeaponEnemy()
{
	WeaponSpawner = CreateDefaultSubobject<UWeaponSpawner>(TEXT("WeaponSpawner"));
}

void AWeaponEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(ReferencedWeapon))
	{
		return;
	}

	LastSpawnedWeapon = WeaponSpawner->Spawn(ReferencedWeapon);
}

void AWeaponEnemy::ActivateAbility()
{
	if (!IsValid(LastSpawnedWeapon))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("LastSpawnedWeapon was not valid."));
		return;
	}

	if (!IsValid(AbilitySystem))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("AbilitySystem was not valid."));
		return;
	}

	if (!HasAuthority())
	{
		UE_LOG(SideScrollerLog, Log, TEXT("No authority."));
		return;
	}

	FGameplayAbilitySpecHandle GameplayAbilitySpecHandle = AbilitySystem->GiveAbility(FGameplayAbilitySpec(LastSpawnedWeapon->Ability.GetDefaultObject(), 1));
	TArray<FGameplayAbilitySpec>& GameplayAbilities = AbilitySystem->GetActivatableAbilities();
	FGameplayAbilityActorInfo* GameplayAbilityActorInfo = AbilitySystem->AbilityActorInfo.Get();
	for (FGameplayAbilitySpec GameplayAbility : GameplayAbilities)
	{
		UFireWeaponAbility* FireWeaponAbility = Cast<UFireWeaponAbility>(GameplayAbility.Ability);

		if (!IsValid(FireWeaponAbility))
		{
			UE_LOG(SideScrollerLog, Error, TEXT("FireWeaponAbility is not valid"));
			continue;
		}

		FireWeaponAbility->ActivateAbility(GameplayAbilitySpecHandle, GameplayAbilityActorInfo, GameplayAbility.ActivationInfo, nullptr);
	}
	//AbilitySystem->InitAbilityActorInfo(this, this);
}
