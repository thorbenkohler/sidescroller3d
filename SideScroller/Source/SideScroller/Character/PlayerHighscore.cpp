// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHighscore.h"
#include "UI/HighScoreWidget.h"
#include "PlayerHighscore.h"
#include "HealthCollector.h"
#include "Utilities/SideScrollerDelegates.h"


// Called when the game starts
void UPlayerHighscore::BeginPlay()
{
	Super::BeginPlay();

	CoinCollector = GetOwner()->FindComponentByClass<UCoinCollector>();
	HealthComponent = GetOwner()->FindComponentByClass<UHealthComponent>();

	USideScrollerDelegates::OnPlayerDied.AddUObject(this, &UPlayerHighscore::ReceiveOnPlayerDied);
	USideScrollerDelegates::OnGameWon.AddUObject(this, &UPlayerHighscore::ReceiveOnGameWon);
}

void UPlayerHighscore::ReceiveOnPlayerDied()
{
	FHighScoreWidgetData HighScoreWidgetData;
	
	if (IsValid(CoinCollector))
	{
		HighScoreWidgetData.CoinAmount = CoinCollector->Coins;
	}
	else
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No Coin collector was found"));
		HighScoreWidgetData.CoinAmount = 0;
	}

	if (IsValid(HealthComponent))
	{
		HighScoreWidgetData.HealthAmount = HealthComponent->Health;
	}
	else
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No Health collector was found"));
		HighScoreWidgetData.HealthAmount = 0;
	}

	HighScoreWidgetData.bWonState = false;
	USideScrollerDelegates::OnShowHighscore.Broadcast(HighScoreWidgetData);
}

void UPlayerHighscore::ReceiveOnGameWon()
{
	FHighScoreWidgetData HighScoreWidgetData;

	if (IsValid(CoinCollector))
	{
		HighScoreWidgetData.CoinAmount = CoinCollector->Coins;
	}
	else
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No Coin collector was found"));
		HighScoreWidgetData.CoinAmount = 0;
	}

	if (IsValid(HealthComponent))
	{
		HighScoreWidgetData.HealthAmount = HealthComponent->Health;
	}
	else
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No Health component was found"));
		HighScoreWidgetData.HealthAmount = 0;
	}

	HighScoreWidgetData.bWonState = true;
	USideScrollerDelegates::OnShowHighscore.Broadcast(HighScoreWidgetData);
}
