// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SideScrollerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Kismet/GameplayStatics.h"
#include "SideScroller.h"
#include "EngineUtils.h"
#include "UI/MainMenu.h"


void ASideScrollerGameMode::BeginPlay()
{
	Super::BeginPlay();

	USideScrollerDelegates::OnStartNewGame.AddUObject(this, &ASideScrollerGameMode::ReceiveOnStartNewGame);
	USideScrollerDelegates::OnStartNewLevel.AddUObject(this, &ASideScrollerGameMode::ReceiveOnStartNewLevel);
	USideScrollerDelegates::OnRestartCurrentLevel.AddUObject(this, &ASideScrollerGameMode::ReceiveOnRestartCurrentLevel);
	USideScrollerDelegates::OnOpenIngameMenu.AddUObject(this, &ASideScrollerGameMode::ReceiveOnOpenIngameMenu);
	USideScrollerDelegates::OnShowHighscore.AddUObject(this, &ASideScrollerGameMode::ReceiveOnShowHighscore);

	InitFirstWidget();
}

void ASideScrollerGameMode::InitFirstWidget()
{
	if (!IsValid(FirstMenu))
	{
		UE_LOG(LogTemp, Error, TEXT("First Menu is not valid."));
		return;
	}

	USideScrollerWidget* SideScrollerWidget = CreateWidget<USideScrollerWidget>(GetWorld(), FirstMenu);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Creating a new widget failed."));
		return;
	}

	if (!SideScrollerWidget->InitializeMenu())
	{
		return;
	}

	USideScrollerDelegates::OnInitFirstWidget.Broadcast();
}

void ASideScrollerGameMode::ReceiveOnStartNewGame()
{
	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("No initial player asset was set"));
		return;
	}

	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("World not found."));
		return;
	}

	CurrentLevelName = FirstLevelName;

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is not valid."));
		return;
	}

	AActor* PlayerStart = ChoosePlayerStart(PlayerController);

	if (!IsValid(PlayerStart))
	{
		UE_LOG(LogTemp, Log, TEXT("PlayerStart not found"));
		return;
	}

	ASideScrollerCharacter* SideScrollerCharacter = World->SpawnActor<ASideScrollerCharacter>(PlayerCharacter);

	if (!IsValid(SideScrollerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("Spawning SideScrollerCharacter failed."));
		return;
	}

	SideScrollerCharacter->SetActorLocation(PlayerStart->GetActorLocation());
	PlayerController->Possess(SideScrollerCharacter);
}

void ASideScrollerGameMode::ReceiveOnStartNewLevel(FName NewLevelName)
{
	UE_LOG(LogTemp, Log, TEXT("Starting Level %s"), *NewLevelName.ToString());
	UGameplayStatics::OpenLevel(GetWorld(), NewLevelName);
	CurrentLevelName = NewLevelName;
}

void ASideScrollerGameMode::ReceiveOnRestartCurrentLevel()
{
	UE_LOG(LogTemp, Log, TEXT("Restarting Level %s"), *CurrentLevelName.ToString());
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
}

void ASideScrollerGameMode::ReceiveOnOpenIngameMenu()
{
	if (!IsValid(IngameMenu))
	{
		UE_LOG(LogTemp, Error, TEXT("No valid Ingame Menu is referenced."));
		return;
	}

	USideScrollerWidget* SideScrollerWidget = CreateWidget<USideScrollerWidget>(GetWorld(), IngameMenu);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Creating Widget failed, when opening IngameMenu."));
		return;
	}

	SideScrollerWidget->InitializeMenu();
}

void ASideScrollerGameMode::ReceiveOnShowHighscore(FHighScoreWidgetData HighScoreWidgetData)
{
	if (!IsValid(GameOverWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("No game over widget was set."));
		return;
	}

	USideScrollerWidget* SideScrollerWidget = CreateWidget<USideScrollerWidget>(GetWorld(), GameOverWidget);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Creating Widget failed, when showing highscore."));
		return;
	}

	if (!SideScrollerWidget->InitializeMenu())
	{
		return;
	}

	UHighScoreWidget* HighScoreWidget = Cast<UHighScoreWidget>(SideScrollerWidget);
	
	if (!IsValid(HighScoreWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("SideScrollerWidget is not a HighScoreWidget."));
		return;
	}
	
	HighScoreWidget->SetData(HighScoreWidgetData);
}