// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerMenuWidget.h"
#include "IngameMenu.generated.h"

UCLASS()
class SIDESCROLLER_API UIngameMenu : public USideScrollerMenuWidget
{
    GENERATED_BODY()

public:
    // Widget replacement for BeginPlay()
    bool Initialize();

    // Closes the menu
    UFUNCTION(BlueprintCallable, Category = "IngameMenu")
    void CloseMenu();
};
