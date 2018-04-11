// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API APlayerWeapon : public AWeapon
{
	GENERATED_BODY()

public:

    // An additional ability this weapon may trigger
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerWeapon")
    TSubclassOf<class UGameplayAbility> AdditionalAbility;
};
