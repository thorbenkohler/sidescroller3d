// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SideScrollerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Kismet/GameplayStatics.h"


ASideScrollerGameMode::ASideScrollerGameMode()
{
}

void ASideScrollerGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitFirstWidget();
	USideScrollerDelegates::OnStartNewGame.AddUObject(this, &ASideScrollerGameMode::ReceiveOnStartNewGame);
	USideScrollerDelegates::OnStartNewLevel.AddUObject(this, &ASideScrollerGameMode::ReceiveOnStartNewLevel);
	USideScrollerDelegates::OnRestartCurrentLevel.AddUObject(this, &ASideScrollerGameMode::ReceiveOnRestartCurrentLevel);
}

void ASideScrollerGameMode::InitFirstWidget()
{
	if (!IsValid(FirstMenu))
	{
		UE_LOG(LogTemp, Error, TEXT("First Menu is not valid."));
		return;
	}
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), FirstMenu);
	if (!IsValid(Widget))
	{
		UE_LOG(LogTemp, Error, TEXT("Creating a new widget failed."));
		return;
	}
	Widget->AddToViewport();
	USideScrollerDelegates::OnInitFirstWidget.Broadcast(Widget);
}

void ASideScrollerGameMode::ReceiveOnStartNewGame()
{
	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("No initial player asset was set"));
		return;
	}
	FString WorldName = GetWorld()->GetMapName();

	// Removing level prefix
	WorldName = WorldName.Replace(TEXT("UEDPIE_0_"), TEXT(""));
	CurrentLevelName = (FName)*WorldName;
	ASideScrollerCharacter* SideScrollerCharacter = GetWorld()->SpawnActor<ASideScrollerCharacter>(PlayerCharacter);
	SideScrollerCharacter->SetActorLocation(FVector(1200.0f, -470.0f, 230.0f));
	GetWorld()->GetFirstPlayerController()->Possess(SideScrollerCharacter);
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
