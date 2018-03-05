// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SideScrollerWidget.h"
#include "HighScoreWidget.generated.h"

// Contains informations about the highscore screen
USTRUCT()
struct FHighScoreWidgetData
{
	GENERATED_BODY()

public:
	int32 CoinAmount;

	int32 HealthAmount;

	uint32 bWonState:1;
};

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API UHighScoreWidget : public USideScrollerWidget
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
	void RestartLevel();

	// The data which is shown on the score board
	void SetData(FHighScoreWidgetData& HighScoreWidgetData);

	// Amount of coins
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
	int32 CoinAmount;

	// Amount of remaining health
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
	int32 HealthAmount;

	// If the game was finished by dying or winning
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
	uint32 bWonState:1;

	// localized text for positive game end
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HighScoreWidget")
	FString GameOverPositive;

	// localized text for negative game end
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HighScoreWidget")
	FString GameOverNegative;
};
