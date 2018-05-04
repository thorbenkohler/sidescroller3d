// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerWidget.h"
#include "SideScrollerHud.generated.h"

UCLASS()
class SIDESCROLLER_API USideScrollerHud : public USideScrollerWidget
{
    GENERATED_BODY()

public:
    // Replacement for BeginPlay() in widgets
    bool Initialize();

	// Sends an additional event to initialize the values
	virtual bool InitializeWidget() override;

    // Displays the coins on the player's HUD
    void ReceiveOnPlayerChangeCoins(int32 Amount);

    // Displays the health on the player's HUD
    void ReceiveOnPlayerChangeHealth(float Amount);

    // Can be used for spawn effects
    UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerHud")
    void InitWidget();

    // Can be used for Hud effects
    UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerHud")
    void ChangeCoinAmount();

    // Can be used for Hud effects
    UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerHud")
    void ChangeHealthAmount();

    // The amount of collected coins
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerHud")
    int32 CoinAmount;

    // The amount of remaining health
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerHud")
    float HealthAmount;
};
