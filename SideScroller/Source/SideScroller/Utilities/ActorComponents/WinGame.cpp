// Fill out your copyright notice in the Description page of Project Settings.

#include "WinGame.h"
#include "Utilities/SideScrollerDelegates.h"

void UWinGame::WinGame()
{
    UE_LOG(SideScrollerLog, Log, TEXT("Game Won is triggered."));
    USideScrollerDelegates::OnGameWon.Broadcast();
}
