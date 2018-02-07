// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerPlayerController.h"

void ASideScrollerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
