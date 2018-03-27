// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "SideScrollerButton.generated.h"

UCLASS()
class SIDESCROLLER_API USideScrollerButton : public UButton
{
    GENERATED_BODY()

public:
    // Used to show hovered visuals
    void SlateHandleHovered();

    // Used to show unhovered visuals
    void SlateHandleUnhovered();
};
