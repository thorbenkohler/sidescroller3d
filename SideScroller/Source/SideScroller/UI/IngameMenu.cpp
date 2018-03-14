// Fill out your copyright notice in the Description page of Project Settings.

#include "IngameMenu.h"
#include "Utilities/SideScrollerDelegates.h"

bool UIngameMenu::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}
	return true;
}

void UIngameMenu::CloseMenu()
{
	this->RemoveFromViewport();

	USideScrollerDelegates::OnCloseIngameMenu.Broadcast();
}
