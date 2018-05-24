// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerPlayerController.h"
#include "Utilities/SideScrollerDelegates.h"

ASideScrollerPlayerController::ASideScrollerPlayerController()
{
    USideScrollerDelegates::OnStartNewGame.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnStartNewGame);
    USideScrollerDelegates::OnInitFirstWidget.AddUObject(this,
                                                         &ASideScrollerPlayerController::ReceiveOnInitFirstWidget);
    USideScrollerDelegates::OnPlayerDied.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnPlayerDied);
    USideScrollerDelegates::OnGameWon.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnGameWon);
    USideScrollerDelegates::OnOpenIngameMenu.AddUObject(this, &ASideScrollerPlayerController::ReceiveOnOpenIngameMenu);
    USideScrollerDelegates::OnCloseIngameMenu.AddUObject(this,
                                                         &ASideScrollerPlayerController::ReceiveOnCloseIngameMenu);
    USideScrollerDelegates::OnRestartAtLastCheckpoint.AddUObject(
        this, &ASideScrollerPlayerController::ReceiveOnRestartAtLastCheckpoint);

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

void ASideScrollerPlayerController::ReceiveOnInitFirstWidget()
{
    SetInputMode(FInputModeGameAndUI());
}

void ASideScrollerPlayerController::ReceiveOnPlayerDied()
{
    SetInputMode(FInputModeUIOnly());
}

void ASideScrollerPlayerController::ReceiveOnGameWon()
{
    SetInputMode(FInputModeUIOnly());
}

void ASideScrollerPlayerController::ReceiveOnOpenIngameMenu()
{
    SetInputMode(FInputModeUIOnly());
}

void ASideScrollerPlayerController::ReceiveOnCloseIngameMenu()
{
    SetInputMode(FInputModeGameOnly());
}

void ASideScrollerPlayerController::ReceiveOnRestartAtLastCheckpoint()
{
    SetInputMode(FInputModeGameOnly());
}

void ASideScrollerPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}
