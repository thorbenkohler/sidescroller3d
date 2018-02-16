// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerDelegates.generated.h"

class ACollectable;
class AWeapon;
class ASideScrollerTriggerBox;

struct FHighScoreWidgetData;

UCLASS()
class SIDESCROLLER_API USideScrollerDelegates : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableAdded, ACollectable*);
	static FOnCollectableAdded OnCollectableAdded;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableWeaponAdded, TSubclassOf<AActor>);
	static FOnCollectableWeaponAdded OnCollectableWeaponAdded;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableCoinAdded, int32);
	static FOnCollectableCoinAdded OnCollectableCoinAdded;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableHealthAdded, int32);
	static FOnCollectableHealthAdded OnCollectableHealthAdded;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerChangeHealth, int32);
	static FOnPlayerChangeHealth OnPlayerChangeHealth;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowWidget, TSubclassOf<UUserWidget>);
	static FOnShowWidget OnShowWidget;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnInitFirstWidget, UUserWidget*);
	static FOnInitFirstWidget OnInitFirstWidget;

	DECLARE_MULTICAST_DELEGATE(FOnStartNewGame);
	static FOnStartNewGame OnStartNewGame;

	DECLARE_MULTICAST_DELEGATE(FOnPlayerDied);
	static FOnPlayerDied OnPlayerDied;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowHighscore, FHighScoreWidgetData);
	static FOnShowHighscore OnShowHighscore;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartNewLevel, FName);
	static FOnStartNewLevel OnStartNewLevel;

	DECLARE_MULTICAST_DELEGATE(FOnRestartCurrentLevel);
	static FOnRestartCurrentLevel OnRestartCurrentLevel;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTriggerBoxEnter, ASideScrollerTriggerBox*);
	static FOnTriggerBoxEnter OnTriggerBoxEnter;

	DECLARE_MULTICAST_DELEGATE(FOnGameWon);
	static FOnGameWon OnGameWon;
};
