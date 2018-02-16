// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "HighScoreWidget.h"
#include "Utilities/SideScrollerDelegates.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	USideScrollerDelegates::OnShowWidget.AddUObject(this, &UMainMenu::ReceiveOnShowWidget);
	USideScrollerDelegates::OnInitFirstWidget.AddUObject(this, &UMainMenu::ReceiveOnInitFirstWidget);
	USideScrollerDelegates::OnShowHighscore.AddUObject(this, &UMainMenu::ReceiveOnShowHighscore);
}

bool UMainMenu::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}
	return true;
}

void UMainMenu::ReceiveOnShowWidget(TSubclassOf<UUserWidget> Widget)
{
	ChangeMenuWidget(Widget);
}

void UMainMenu::ReceiveOnInitFirstWidget(UUserWidget* Widget)
{
	if (!IsValid(Widget))
	{
		UE_LOG(LogTemp, Error, TEXT("There was a problem with the main menu creatiion."))
		return;
	}
	CurrentWidget = Widget;
}

void UMainMenu::ReceiveOnShowHighscore(int32 Amount)
{
	if (!IsValid(GameOverWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("No game over widget was set."));
		return;
	}

	ChangeMenuWidget(GameOverWidget);

	if (!IsValid(CurrentWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("There was a problem spawning the Highscore widget."));
		return;
	}

	UHighScoreWidget* HighScoreWidget = Cast<UHighScoreWidget>(CurrentWidget);
	
	if (!IsValid(HighScoreWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentWidget is not a HighScoreWidget."));
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Successfully created Highscore Widget with %d Coins."), Amount);
	HighScoreWidget->CoinAmount = Amount;
}

void UMainMenu::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (IsValid(CurrentWidget))
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (!IsValid(NewWidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("NewWidgetClass is not valid."));
		return;
	}

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
	if (!IsValid(CurrentWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Creating a new widget failed."));
		return;
	}
	CurrentWidget->AddToViewport();
}

void UMainMenu::StartNewGame()
{
	USideScrollerDelegates::OnStartNewGame.Broadcast();
}