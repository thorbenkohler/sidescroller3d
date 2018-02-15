// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreWidget.h"
#include "Utilities/SideScrollerDelegates.h"

UHighScoreWidget::UHighScoreWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	USideScrollerDelegates::OnSetHighscore.AddUObject(this, &UHighScoreWidget::ReceiveOnSetHighscore);
}

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

void UHighScoreWidget::ReceiveOnSetHighscore(int32 Amount)
{
	CoinAmount += Amount;
	UE_LOG(LogTemp, Log, TEXT("%d Coin were added and result is %d"), Amount, CoinAmount);
}
