// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/SideScrollerDelegates.h"


ASideScrollerPlayerController::ASideScrollerPlayerController()
{
	USideScrollerDelegates::OnStartNewGame.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnStartNewGame);
	USideScrollerDelegates::OnInitFirstWidget.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnInitFirstWidget);
	USideScrollerDelegates::OnPlayerDied.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnPlayerDied);
	USideScrollerDelegates::OnGameWon.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnGameWon);
}

void ASideScrollerPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ASideScrollerPlayerController::ReceiveOnStartNewGame()
{
	SetInputMode(FInputModeGameOnly());
}

void ASideScrollerPlayerController::ReceiveOnInitFirstWidget(UUserWidget* Widget)
{
	SetInputMode(FInputModeGameAndUI());
}

void ASideScrollerPlayerController::ReceiveOnPlayerDied()
{
	SetInputMode(FInputModeGameAndUI());
}

void ASideScrollerPlayerController::ReceiveOnGameWon()
{
	SetInputMode(FInputModeGameAndUI());
}

void ASideScrollerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}