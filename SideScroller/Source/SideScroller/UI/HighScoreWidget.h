// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreWidget.generated.h"

// Contains informations about the highscore screen
USTRUCT()
struct FHighScoreWidgetData
{
	GENERATED_BODY()

public:
	int32 CoinAmount;

	uint32 bWonState:1;
};

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API UHighScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize();

	UFUNCTION(BlueprintImplementableEvent, Category = "HighScoreWidget")
	void InitWidget();

	UFUNCTION(BlueprintCallable, Category = "HighScoreWidget")
	void RestartLevel();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
	int32 CoinAmount;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
	uint32 bWonState:1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HighScoreWidget")
	FString GameOverPositive;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "HighScoreWidget")
	FString GameOverNegative;
};
