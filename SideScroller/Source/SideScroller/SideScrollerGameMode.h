// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SideScrollerGameMode.generated.h"

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

	void InitFirstWidget();
};
