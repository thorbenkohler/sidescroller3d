// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Interfaces/ComboResettable.h"
#include "ComboReset.generated.h"

UCLASS(Blueprintable)
class SIDESCROLLER_API UComboReset : public UActorComponent
{
    GENERATED_BODY()

public:
    UComboReset();

private:
    void ReceiveOnCharacterLanded(const FHitResult& Hit);
};
