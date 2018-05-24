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

void UHighScoreWidget::RestartAtLastCheckpoint()
{
    this->RemoveFromViewport();

    USideScrollerDelegates::OnRestartAtLastCheckpoint.Broadcast();
}

void UHighScoreWidget::SetData(FHighScoreWidgetData& HighScoreWidgetData)
{
    CoinAmount = HighScoreWidgetData.CoinAmount;
    HealthAmount = HighScoreWidgetData.HealthAmount;
    bWonState = HighScoreWidgetData.bWonState;
    DataSet();
}
