// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SideScrollerPlayerController.generated.h"

/**
*
*/
UCLASS()
class SIDESCROLLER_API ASideScrollerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Handles the cursor and sets the according input mode
	void ReceiveOnStartNewGame();

	// Handles the cursor and sets the according input mode
	void ReceiveOnInitFirstWidget(UUserWidget* Widget);

	// Handles the cursor and sets the according input mode
	void ReceiveOnPlayerDied();

	// Handles the cursor and sets the according input mode
	void ReceiveOnGameWon();

	// Used for Ui controlling
	void SetupInputComponent();

};
