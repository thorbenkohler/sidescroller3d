// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTask_SpawnProjectile.h"



UAbilityTask_SpawnProjectile::UAbilityTask_SpawnProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAbilityTask_SpawnProjectile* UAbilityTask_SpawnProjectile::CreateMyTask(UGameplayAbility* OwningAbility, FName TaskInstanceName, float ExampleVariable)
{

	UAbilityTask_SpawnProjectile* AbilityTask_SpawnProjectile = NewAbilityTask<UAbilityTask_SpawnProjectile>(OwningAbility, TaskInstanceName);
	return AbilityTask_SpawnProjectile;
}

void UAbilityTask_SpawnProjectile::Activate()
{
}
