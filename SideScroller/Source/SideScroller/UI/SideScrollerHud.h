// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SideScrollerHud.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API USideScrollerHud : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize();

	virtual void ReceiveOnCollectableCoinAdded(int32 Amount);
	
	virtual void ReceiveOnPlayerChangeHealth(int32 Amount);

	UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerHud")
	void InitWidget();

	// Can be used for Hud effects
	UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerHud")
	void ChangeCoinAmount();

	// Can be used for Hud effects
	UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerHud")
	void ChangeHealthAmount();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "SideScrollerHud")
	int32 CoinAmount;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SideScrollerHud")
	int32 HealthAmount;
};
