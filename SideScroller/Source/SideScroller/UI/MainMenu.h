// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerMenuWidget.h"
#include "MainMenu.generated.h"

UCLASS()
class SIDESCROLLER_API UMainMenu : public USideScrollerMenuWidget
{
    GENERATED_BODY()

public:
    // Used as BeginPlay replacement
    bool Initialize();
};
