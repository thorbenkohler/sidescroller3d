// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "PlayerWeapon.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerWeapon : public UInterface
{
    GENERATED_BODY()
};

class SIDESCROLLER_API IPlayerWeapon
{
    GENERATED_BODY()

public:

	virtual TArray<TSubclassOf<class UGameplayAbility>> GetAdditionalAbilities() = 0;
};
