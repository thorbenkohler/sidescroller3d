// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASideScrollerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
