// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RangedWeapon.h"
#include "Interfaces/PlayerWeapon.h"
#include "RangedPlayerWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API ARangedPlayerWeapon : public ARangedWeapon, public IPlayerWeapon
{
	GENERATED_BODY()

public:

	TSubclassOf<class UGameplayAbility> GetAdditionalAbility() override
	{ 
		return AdditionalAbility; 
	}

    // An additional ability this weapon may trigger
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged|Player")
    TSubclassOf<class UGameplayAbility> AdditionalAbility;
};
