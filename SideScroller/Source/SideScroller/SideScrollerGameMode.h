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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<UUserWidget> FirstMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	TSubclassOf<ASideScrollerCharacter> PlayerCharacter;

	void InitFirstWidget();

	void ReceiveOnStartNewGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerGameMode")
	FName CurrentLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerGameMode")
	FName LevelName;

	void ReceiveOnStartNewLevel(FName LevelName);

	void ReceiveOnRestartCurrentLevel();
};
