// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHighscore.h"
#include "HealthCollector.h"

#include "UI/HighScoreWidget.h"

#include "Interfaces/HealthInterface.h"

#include "Abilities/AttributeSets/HealthAttributeSet.h"

#include "Utilities/SideScrollerDelegates.h"


// Called when the game starts
void UPlayerHighscore::BeginPlay()
{
	Super::BeginPlay();

	CoinCollector = GetOwner()->FindComponentByClass<UCoinCollector>();
	HealthComponent = Cast<IHealthInterface>(GetOwner())->GetHealthComponent();

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
        HighScoreWidgetData.HealthAmount =
            HealthComponent->AbilitySystem->GetNumericAttribute(UHealthAttributeSet::HealthAttribute());
    }
	else
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No HealthComponent was found"));
		HighScoreWidgetData.HealthAmount = 0.0f;
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
        HighScoreWidgetData.HealthAmount =
            HealthComponent->AbilitySystem->GetNumericAttribute(UHealthAttributeSet::HealthAttribute());
	}
	else
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No Health component was found"));
		HighScoreWidgetData.HealthAmount = 0.0f;
	}

	HighScoreWidgetData.bWonState = true;
	USideScrollerDelegates::OnShowHighscore.Broadcast(HighScoreWidgetData);
}
