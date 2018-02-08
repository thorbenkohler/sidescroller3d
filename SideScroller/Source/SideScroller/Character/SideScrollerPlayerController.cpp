// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASideScrollerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());

	//if (!MainMenu->IsValidLowLevel())
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Reference not found."))
	//	return;
	//}

	//SideScrollerMainMenu = CreateWidget<UUserWidget>(this, MainMenu);
	//if (!SideScrollerMainMenu->IsValidLowLevel())
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Creating the main menu widget failed."))
	//	return;
	//}
	//SideScrollerMainMenu->AddToViewport();
	//bShowMouseCursor = true;
}
