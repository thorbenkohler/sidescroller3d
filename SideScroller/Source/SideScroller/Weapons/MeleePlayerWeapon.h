// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MeleeWeapon.h"
#include "Interfaces/PlayerWeapon.h"
#include "MeleePlayerWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API AMeleePlayerWeapon : public AMeleeWeapon, public IPlayerWeapon
{
	GENERATED_BODY()

public:

	TArray<TSubclassOf<class UGameplayAbility>> GetAdditionalAbilities() override
	{ 
		return AdditionalAbilities; 
	}

    // An additional ability this weapon may trigger
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee|Player")
    TArray<TSubclassOf<class UGameplayAbility>> AdditionalAbilities;
};
