// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Utilities/SideScrollerDelegates.h"

bool UMainMenu::Initialize()
{
    bool Succesful = Super::Initialize();
    if (!Succesful)
    {
        return false;
    }
    return true;
}
