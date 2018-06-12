// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "ComboResettable.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UComboResettable : public UInterface
{
    GENERATED_BODY()
};

class SIDESCROLLER_API IComboResettable
{
    GENERATED_BODY()

public:
    virtual void ComboReset() = 0;
};
