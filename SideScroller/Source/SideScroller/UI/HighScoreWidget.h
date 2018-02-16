// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreWidget.generated.h"

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

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
	int32 CoinAmount;

	UFUNCTION(BlueprintCallable, Category = "HighScoreWidget")
	void RestartLevel();
};
