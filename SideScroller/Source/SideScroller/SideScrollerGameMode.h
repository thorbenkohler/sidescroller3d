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

public:
	ASideScrollerGameMode();

protected:
	// Called when the game starts.
	virtual void BeginPlay() override;

	void InitFirstWidget();

	void ReceiveOnStartNewGame();

	void ReceiveOnStartNewLevel(FName LevelName);

	void ReceiveOnRestartCurrentLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<UUserWidget> FirstMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<ASideScrollerCharacter> PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerGameMode")
	FName CurrentLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	FName LevelName;
};
