// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSpawner.h"
#include "Weapons/Weapon.h"
#include "Weapons/MeleeWeapon.h"
#include "Interfaces/PlayerWeapon.h"
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

    AActor* Owner = GetOwner();
    Weapon->WeaponOwner = Owner;
    Weapon->BindDelegates();

	AEnemy* Enemy = Cast<AEnemy>(Owner);

	if (IsValid(Enemy))
	{
        FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative,
                                        EAttachmentRule::KeepWorld, false);
        Weapon->AttachToComponent(Enemy->StaticMeshComponent, Rules, WeaponSocketName);
		return Weapon;
	}

    IPlayerWeapon* PlayerWeapon = Cast<IPlayerWeapon>(Weapon);

    if (!PlayerWeapon)
    {
        return Weapon;
    }

    ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

    if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Player Weapon %s without a valid owner was spawned."),
               *Weapon->GetName());
        return Weapon;
    }

    TSubclassOf<class UGameplayAbility> Ability = Weapon->Ability;

    if (!IsValid(Ability))
    {
        UE_LOG(SideScrollerLog, Warning, TEXT("Player Weapon %s without a ability was collected."),
               *Weapon->GetName());
        return Weapon;
    }

	USideScrollerAbilitySystemComponent* AbilitySystem = SideScrollerCharacter->AbilitySystem;

	if (!IsValid(AbilitySystem))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("AbilitySystem in WeaponSpawner is not valid."));
		return Weapon;
	}

	AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, (uint32)Weapon->AbilitySlot));

    TArray<TSubclassOf<class UGameplayAbility>> AdditionalAbilities = PlayerWeapon->GetAdditionalAbilities();

	for (auto AdditionalAbility : AdditionalAbilities)
	{
		if (!IsValid(AdditionalAbility))
		{
			return Weapon;
		}

		AbilitySystem->GiveAbility(FGameplayAbilitySpec(AdditionalAbility.GetDefaultObject(), 1));
	}

    return Weapon;
}
