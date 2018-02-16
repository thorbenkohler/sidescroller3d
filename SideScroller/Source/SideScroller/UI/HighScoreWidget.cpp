// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreWidget.h"
#include "Utilities/SideScrollerDelegates.h"

bool UHighScoreWidget::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}
	InitWidget();
	return true;
}

void UHighScoreWidget::RestartLevel()
{
	USideScrollerDelegates::OnRestartCurrentLevel.Broadcast();
}
