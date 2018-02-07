// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SideScrollerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "SideScrollerGameMode.generated.h"

UCLASS(minimalapi)
class ASideScrollerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASideScrollerGameMode();

	// Remove the current menu widget and create a new one from the specified class, if provided.
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	// Called when the game starts.
	virtual void BeginPlay() override;

	// The widget class we will use as our menu when the game starts.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	// The widget instance that we are using as our menu.
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
