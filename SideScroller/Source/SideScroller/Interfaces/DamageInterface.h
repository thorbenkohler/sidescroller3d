// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
    GENERATED_BODY()
};

class SIDESCROLLER_API IDamageInterface
{
    GENERATED_BODY()

public:
    virtual void DamageTaken(int32 IncomingDamage) = 0;
};
