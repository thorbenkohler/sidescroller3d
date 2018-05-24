// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SideScrollerPlayerController.generated.h"

UCLASS()
class SIDESCROLLER_API ASideScrollerPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASideScrollerPlayerController();

    virtual void BeginPlay() override;

    // Handles the cursor and sets the according input mode
    void ReceiveOnStartNewGame();

    // Handles the cursor and sets the according input mode
    void ReceiveOnInitFirstWidget();

    // Handles the cursor and sets the according input mode
    void ReceiveOnPlayerDied();

    // Handles the cursor and sets the according input mode
    void ReceiveOnGameWon();

    // Handles the cursor and sets the according input mode
    void ReceiveOnOpenIngameMenu();

    // Handles the cursor and sets the according input mode
    void ReceiveOnCloseIngameMenu();

    // Handles the cursor and sets the according input mode
	void ReceiveOnRestartAtLastCheckpoint();

    // Used for Ui controlling
    void SetupInputComponent();
};
