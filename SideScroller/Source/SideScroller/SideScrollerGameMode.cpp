// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SideScrollerGameMode.h"
#include "Collectables/Collectable.h"
#include "UObject/ConstructorHelpers.h"


ASideScrollerGameMode::ASideScrollerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASideScrollerGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);
}

void ASideScrollerGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget->IsValidLowLevel())
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass->IsValidLowLevel())
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (!CurrentWidget->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Error, TEXT("Creating a new widget failed."));
			return;
		}
		CurrentWidget->AddToViewport();
	}
}