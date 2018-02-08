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

	// Reference to the UMG Asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> MainMenu;

	// Variable to hold the widget After Creating it.
	UUserWidget* SideScrollerMainMenu;
};
