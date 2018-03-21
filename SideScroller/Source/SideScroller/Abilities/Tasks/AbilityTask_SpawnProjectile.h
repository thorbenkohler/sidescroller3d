// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityTask.h"
#include "AbilityTask_SpawnProjectile.generated.h"


UCLASS()
class SIDESCROLLER_API UAbilityTask_SpawnProjectile : public UAbilityTask
{
	GENERATED_UCLASS_BODY()

public:
	UAbilityTask_SpawnProjectile* CreateMyTask(UGameplayAbility* OwningAbility, FName TaskInstanceName, float ExampleVariable);

	void Activate();
};
