// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SideScrollerGameMode.generated.h"

class ASideScrollerCharacter;

UCLASS(minimalapi)
class ASideScrollerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts.
	virtual void BeginPlay() override;

	// Shows the first widget after game start up
	void InitFirstWidget();

	// Spawns the Player and sets the level name after closing the menu
	void ReceiveOnStartNewGame();

	// Can be used to start a new level
	void ReceiveOnStartNewLevel(FName LevelName);

	// Restarts the current level
	void ReceiveOnRestartCurrentLevel();

	// The menu which gets shown after game start up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<UUserWidget> FirstMenu;

	// The character of the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<ASideScrollerCharacter> PlayerCharacter;

	// Gets set everytime the game starts or the level changes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerGameMode")
	FName CurrentLevelName;

	// Gets started, when a new game was chosen by the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	FName FirstLevelName;
};
