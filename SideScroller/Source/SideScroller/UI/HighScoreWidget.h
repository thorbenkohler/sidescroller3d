// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerMenuWidget.h"
#include "HighScoreWidget.generated.h"

// Contains informations about the highscore screen
USTRUCT()
struct FHighScoreWidgetData
{
    GENERATED_BODY()

public:
    int32 CoinAmount;

    float HealthAmount;

    uint32 bWonState : 1;
};

UCLASS()
class SIDESCROLLER_API UHighScoreWidget : public USideScrollerMenuWidget
{
    GENERATED_BODY()

public:
    // Widget replacement for BeginPlay()
    bool Initialize();

    // Can be used for spawning effects
    UFUNCTION(BlueprintImplementableEvent, Category = "HighScoreWidget")
    void InitWidget();

    // Restarts the current level
    UFUNCTION(BlueprintCallable, Category = "HighScoreWidget")
    void RestartAtLastCheckpoint();

    // Can be used as post-construct method for effects and sound according to data
    UFUNCTION(BlueprintImplementableEvent, Category = "HighScoreWidget")
    void DataSet();

    // The data which is shown on the score board
    void SetData(FHighScoreWidgetData& HighScoreWidgetData);

    // Amount of coins
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
    int32 CoinAmount;

    // Amount of remaining health
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
    float HealthAmount;

    // If the game was finished by dying or winning
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
    uint32 bWonState : 1;

    // localized text for positive game end
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HighScoreWidget")
    FString GameOverPositive;

    // localized text for negative game end
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HighScoreWidget")
    FString GameOverNegative;
};
