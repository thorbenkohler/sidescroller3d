// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/SideScrollerDelegates.h"

void ASideScrollerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	USideScrollerDelegates::OnStartNewGame.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnStartNewGame);
	USideScrollerDelegates::OnInitFirstWidget.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnInitFirstWidget);
	USideScrollerDelegates::OnPlayerDied.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnPlayerDied);
	USideScrollerDelegates::OnGameWon.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnGameWon);
}

void ASideScrollerPlayerController::ReceiveOnStartNewGame()
{
	bShowMouseCursor = 0;
	SetInputMode(FInputModeGameOnly());
}

void ASideScrollerPlayerController::ReceiveOnInitFirstWidget(UUserWidget* Widget)
{
	bShowMouseCursor = 1;
	SetInputMode(FInputModeGameAndUI());
}

void ASideScrollerPlayerController::ReceiveOnPlayerDied()
{
	bShowMouseCursor = 1;
	SetInputMode(FInputModeGameAndUI());
}

void ASideScrollerPlayerController::ReceiveOnGameWon()
{
	bShowMouseCursor = 1;
	SetInputMode(FInputModeGameAndUI());
}

void ASideScrollerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}