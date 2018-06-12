// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Interfaces/ComboResettable.h"
#include "TouchErosion.generated.h"

UCLASS(Blueprintable)
class SIDESCROLLER_API UTouchErosion : public UActorComponent, public IComboResettable
{
    GENERATED_BODY()
        
public:
    UFUNCTION(BlueprintImplementableEvent, Category = "SideScroller")
    void ComboReset();
};
