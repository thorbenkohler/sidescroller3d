// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerWidget.h"
#include "Utilities/SideScrollerDelegates.h"

bool USideScrollerWidget::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}
	return true;
}
