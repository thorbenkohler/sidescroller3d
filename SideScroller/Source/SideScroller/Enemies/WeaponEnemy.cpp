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
        UE_LOG(SideScrollerLog, Warning, TEXT("Weapon enemy has no referenced weapon."));
        return;
    }

	AWeapon* SpawnedWeapon = WeaponSpawner->Spawn(ReferencedWeapon);

    if (!IsValid(SpawnedWeapon))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("SpawnedWeapon was not valid."));
        return;
    }

	ARangedWeapon* RangedWeapon = Cast<ARangedWeapon>(SpawnedWeapon);

	if (!IsValid(RangedWeapon))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("SpawnedWeapon is in WeaponEnemy not of type ARangedWeapon"));
		return;
	}

	CurrentlyEquippedRangedWeapon = RangedWeapon;

    if (!IsValid(CurrentlyEquippedRangedWeapon))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("CurrentlyEquippedRangedWeapon was not valid."));
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

	TSubclassOf<class UGameplayAbility> Ability = CurrentlyEquippedRangedWeapon->Ability;

	if (!IsValid(Ability))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Ability of Weapon enemy %s is invalid."), *GetName());
		return;
	}

    FGameplayAbilitySpec GameplayAbilitySpec(Ability.GetDefaultObject(), 1);
    FGameplayAbilitySpecHandle GameplayAbilitySpecHandle = AbilitySystem->GiveAbility(GameplayAbilitySpec);
    AbilitySystem->InitAbilityActorInfo(this, this);

    for (FGameplayAbilitySpec TempGameplayAbilitySpec : AbilitySystem->GetActivatableAbilities())
    {
        TArray<UGameplayAbility*> InstancedAbilities = TempGameplayAbilitySpec.GetAbilityInstances();
        for (UGameplayAbility* TempInstancedAbility : InstancedAbilities)
        {
            if (!IsValid(TempInstancedAbility))
            {
                UE_LOG(SideScrollerLog, Error, TEXT("InstancedAbility is not valid"));
                continue;
            }

            InstancedAbility = TempInstancedAbility;
        }
    }
}

void AWeaponEnemy::ActivateAbility()
{
    if (!IsValid(InstancedAbility))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("InstancedAbility is not valid"));
        return;
    }

    UFireWeaponAbility* FireWeaponAbility = Cast<UFireWeaponAbility>(InstancedAbility);

    if (!IsValid(FireWeaponAbility))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("FireWeaponAbility is not valid"));
        return;
    }

    FGameplayAbilityActorInfo ActorInfo(FireWeaponAbility->GetActorInfo());
    FGameplayAbilityActorInfo* Temp = &ActorInfo;

    FireWeaponAbility->ActivateAbility(FireWeaponAbility->GetCurrentAbilitySpecHandle(), Temp,
                                       FireWeaponAbility->GetCurrentActivationInfo(), nullptr);
}
