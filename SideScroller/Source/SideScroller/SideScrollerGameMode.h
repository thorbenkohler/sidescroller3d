// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SideScrollerGameMode.generated.h"

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

	// Shows the ingame menu
	void ReceiveOnOpenIngameMenu();

	// Shows the highscore after the player's death
	void ReceiveOnShowHighscore(struct FHighScoreWidgetData HighScoreWidgetData);

	// Is used for initializing the game and respawning
	class ASideScrollerCharacter* SpawnCharacterAtLocation(FVector InLocation);

	// The menu which gets shown after game start up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<UUserWidget> FirstMenu;

	// A menu which is displayed after the game was started
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<UUserWidget> IngameMenu;

	// Used to display the highscore and respawn button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<UUserWidget> GameOverWidget;

	// Used to display the highscore and respawn button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<UUserWidget> Hud;

	// The character of the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<ASideScrollerCharacter> PlayerCharacter;

	// Gets set everytime the game starts or the level changes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerGameMode")
	FName CurrentLevelName;

	// Gets started, when a new game was chosen by the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	FName FirstLevelName;

	// Name of menu scene
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	FName MenuLevelName;

	// Reference to the current player character
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category ="SideScrollerGameMode")
	class ASideScrollerCharacter* SideScrollerCharacter;
};
