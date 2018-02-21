// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHighscore.h"
#include "UI/HighScoreWidget.h"
#include "PlayerHighscore.h"
#include "HealthCollector.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UPlayerHighscore::UPlayerHighscore()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlayerHighscore::BeginPlay()
{
	Super::BeginPlay();

	CoinCollector = GetOwner()->FindComponentByClass<UCoinCollector>();
	HealthCollector = GetOwner()->FindComponentByClass<UHealthCollector>();

	USideScrollerDelegates::OnPlayerDied.AddUObject(this, &UPlayerHighscore::ReceiveOnPlayerDied);
	USideScrollerDelegates::OnGameWon.AddUObject(this, &UPlayerHighscore::ReceiveOnGameWon);
}

// Called every frame
void UPlayerHighscore::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
		UE_LOG(LogTemp, Error, TEXT("No Coin collector was found"));
		HighScoreWidgetData.CoinAmount = 0;
	}

	if (IsValid(HealthCollector))
	{
		HighScoreWidgetData.HealthAmount = HealthCollector->Health;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Health collector was found"));
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
		UE_LOG(LogTemp, Error, TEXT("No Coin collector was found"));
		HighScoreWidgetData.CoinAmount = 0;
	}

	if (IsValid(HealthCollector))
	{
		HighScoreWidgetData.HealthAmount = HealthCollector->Health;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Health collector was found"));
		HighScoreWidgetData.HealthAmount = 0;
	}

	HighScoreWidgetData.bWonState = true;
	USideScrollerDelegates::OnShowHighscore.Broadcast(HighScoreWidgetData);
}
