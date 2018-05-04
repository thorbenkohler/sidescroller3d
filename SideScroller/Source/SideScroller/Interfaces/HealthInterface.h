// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Utilities/ActorComponents/HealthComponent.h"
#include "HealthInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
    GENERATED_BODY()
};

class SIDESCROLLER_API IHealthInterface
{
    GENERATED_BODY()

public:
    virtual UHealthComponent* GetHealthComponent() const = 0;

	virtual void OnDeath() const = 0;
};
