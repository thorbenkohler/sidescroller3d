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


	FString TempCurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	if (MenuLevelName.ToString() != TempCurrentLevelName)
	{
		USideScrollerDelegates::OnStartNewGame.AddUObject(this, &ASideScrollerGameMode::ReceiveOnStartNewGame);
		USideScrollerDelegates::OnStartNewLevel.AddUObject(this, &ASideScrollerGameMode::ReceiveOnStartNewLevel);
		USideScrollerDelegates::OnRestartCurrentLevel.AddUObject(this, &ASideScrollerGameMode::ReceiveOnRestartCurrentLevel);
		USideScrollerDelegates::OnOpenIngameMenu.AddUObject(this, &ASideScrollerGameMode::ReceiveOnOpenIngameMenu);
		USideScrollerDelegates::OnShowHighscore.AddUObject(this, &ASideScrollerGameMode::ReceiveOnShowHighscore);
		USideScrollerDelegates::OnStartNewGame.Broadcast();
		return;
	}

	InitFirstWidget();
}

void ASideScrollerGameMode::InitFirstWidget()
{
	if (!IsValid(FirstMenu))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("First Menu is not valid."));
		return;
	}

	USideScrollerWidget* SideScrollerWidget = CreateWidget<USideScrollerWidget>(GetWorld(), FirstMenu);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Creating the first menu failed."));
		return;
	}

	if (!SideScrollerWidget->InitializeWidget())
	{
		return;
	}

	USideScrollerDelegates::OnInitFirstWidget.Broadcast();
}

void ASideScrollerGameMode::ReceiveOnStartNewGame()
{
	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("World not found."));
		return;
	}

	CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!IsValid(PlayerController))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("PlayerController is not valid."));
		return;
	}

	AActor* PlayerStart = ChoosePlayerStart(PlayerController);

	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No initial player asset was set"));
		return;
	}

	ASideScrollerCharacter* SideScrollerCharacter = World->SpawnActor<ASideScrollerCharacter>(PlayerCharacter);

	if (!IsValid(PlayerStart))
	{
		UE_LOG(SideScrollerLog, Log, TEXT("PlayerStart not found"));
		return;
	}

	SideScrollerCharacter->SetActorLocation(PlayerStart->GetActorLocation());

    if (!IsValid(SideScrollerCharacter))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Spawning SideScrollerCharacter failed."));
		return;
	}

	PlayerController->Possess(SideScrollerCharacter);

	if (!IsValid(Hud))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No valid Hud was assigned."));
		return;
	}

	USideScrollerWidget* SideScrollerWidget = CreateWidget<USideScrollerWidget>(GetWorld(), Hud);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Creating a Hud failed."));
		return;
	}

	if (!SideScrollerWidget->InitializeWidget())
	{
		return;
	}
}

void ASideScrollerGameMode::ReceiveOnStartNewLevel(FName NewLevelName)
{
	UE_LOG(SideScrollerLog, Log, TEXT("Starting Level %s"), *NewLevelName.ToString());
	UGameplayStatics::OpenLevel(GetWorld(), NewLevelName);
	CurrentLevelName = NewLevelName;
}

void ASideScrollerGameMode::ReceiveOnRestartCurrentLevel()
{
	UE_LOG(SideScrollerLog, Log, TEXT("Restarting Level %s"), *CurrentLevelName.ToString());
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
}

void ASideScrollerGameMode::ReceiveOnOpenIngameMenu()
{
	if (!IsValid(IngameMenu))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No valid Ingame Menu is referenced."));
		return;
	}

	USideScrollerWidget* SideScrollerWidget = CreateWidget<USideScrollerWidget>(GetWorld(), IngameMenu);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Creating Widget failed, when opening IngameMenu."));
		return;
	}

	SideScrollerWidget->InitializeWidget();
}

void ASideScrollerGameMode::ReceiveOnShowHighscore(FHighScoreWidgetData HighScoreWidgetData)
{
	if (!IsValid(GameOverWidget))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No game over widget was set."));
		return;
	}

	USideScrollerWidget* SideScrollerWidget = CreateWidget<USideScrollerWidget>(GetWorld(), GameOverWidget);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Creating Widget failed, when showing highscore."));
		return;
	}

	if (!SideScrollerWidget->InitializeWidget())
	{
		return;
	}

	UHighScoreWidget* HighScoreWidget = Cast<UHighScoreWidget>(SideScrollerWidget);
	
	if (!IsValid(HighScoreWidget))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("SideScrollerWidget is not a HighScoreWidget."));
		return;
	}
	
	HighScoreWidget->SetData(HighScoreWidgetData);
}