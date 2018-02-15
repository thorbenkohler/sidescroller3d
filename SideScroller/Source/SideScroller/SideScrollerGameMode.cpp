// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SideScrollerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/SideScrollerDelegates.h"


ASideScrollerGameMode::ASideScrollerGameMode()
{
}

void ASideScrollerGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitFirstWidget();
}

void ASideScrollerGameMode::InitFirstWidget()
{
	if (!IsValid(FirstMenu))
	{
		UE_LOG(LogTemp, Error, TEXT("First Menu is not valid."));
		return;
	}
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), FirstMenu);
	if (!IsValid(Widget))
	{
		UE_LOG(LogTemp, Error, TEXT("Creating a new widget failed."));
		return;
	}
	Widget->AddToViewport();
	USideScrollerDelegates::OnInitFirstWidget.Broadcast(Widget);
}
