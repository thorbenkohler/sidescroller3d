// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

struct FHighScoreWidgetData;

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	// Used as BeginPlay replacement
	bool Initialize();

	// Switch between widgets
	virtual void ReceiveOnShowWidget(TSubclassOf<UUserWidget> Widget);

	// Used as initial event coming from the game mode to show the first menu in the game
	virtual void ReceiveOnInitFirstWidget(UUserWidget* Widget);

	// Shows the highscore after the player's death
	void ReceiveOnShowHighscore(FHighScoreWidgetData HighScoreWidgetData);

	// Remove the current menu widget and create a new one from the specified class, if provided.
	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	// Executes when the play game button in the menu was pressed
	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void StartNewGame();

	// Gets shown right after initial game startup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainMenu")
	TSubclassOf<UUserWidget> StartMenu;

	// Used to display the highscore and respawn button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainMenu")
	TSubclassOf<UUserWidget> GameOverWidget;

	// The widget instance that we are using as our menu.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MainMenu")
	UUserWidget* CurrentWidget;
};
