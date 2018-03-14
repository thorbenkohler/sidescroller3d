// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SideScrollerWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API UMainMenu : public USideScrollerWidget
{
	GENERATED_BODY()

public:
	// Used as BeginPlay replacement
	bool Initialize();

	// Executes when the play game button in the menu was pressed
	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void StartNewGame();
};
