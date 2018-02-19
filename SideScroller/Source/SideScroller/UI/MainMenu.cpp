// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "HighScoreWidget.h"
#include "Utilities/SideScrollerDelegates.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	USideScrollerDelegates::OnInitFirstWidget.AddUObject(this, &UMainMenu::ReceiveOnInitFirstWidget);
}

bool UMainMenu::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}
	USideScrollerDelegates::OnShowWidget.AddUObject(this, &UMainMenu::ReceiveOnShowWidget);
	USideScrollerDelegates::OnShowHighscore.AddUObject(this, &UMainMenu::ReceiveOnShowHighscore);
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

void UMainMenu::ReceiveOnShowHighscore(FHighScoreWidgetData HighScoreWidgetData)
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
	
	UE_LOG(LogTemp, Log, TEXT("Successfully created Highscore Widget with %d Coins."), HighScoreWidgetData.CoinAmount);
	HighScoreWidget->CoinAmount = HighScoreWidgetData.CoinAmount;
	HighScoreWidget->bWonState = HighScoreWidgetData.bWonState;
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