// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "HighScoreWidget.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Blueprint/WidgetTree.h"


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

	UWidgetTree* WidgetTree = CurrentWidget->WidgetTree;

	//TArray<UWidget*> Widgets;
	//WidgetTree->GetAllWidgets(Widgets);
	//for (UWidget* TempWidget : Widgets)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Widget %s"), *TempWidget->GetName());
	//}
	UWidget* PlayGameButton = WidgetTree->FindWidget(FName("PlayGameButton"));

	if (!IsValid(PlayGameButton))
	{
		UE_LOG(LogTemp, Error, TEXT("No valid Widget found."));
		return;
	}

	UWorld* World = CurrentWidget->GetWorld();

	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("The world is invalid."));
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("No valid PlayerController found."));
		return;
	}

	PlayGameButton->SetUserFocus(PlayerController);
}

void UMainMenu::ReceiveOnShowHighscore(FHighScoreWidgetData HighScoreWidgetData)
{
	// Checking the referenced Widget
	if (!IsValid(GameOverWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("No game over widget was set."));
		return;
	}

	// Setting the Referenced Widget as CurrentWidget
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
	
	HighScoreWidget->SetData(HighScoreWidgetData);
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