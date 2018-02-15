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
	UHighScoreWidget(const FObjectInitializer& ObjectInitializer);

	bool Initialize();

	virtual void ReceiveOnSetHighscore(int32 Amount);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "HighScoreWidget")
	void InitWidget();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "HighScoreWidget")
	int32 CoinAmount;
};
