// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "HighScoreWidget.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Blueprint/WidgetTree.h"


bool UMainMenu::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}

	USideScrollerDelegates::OnInitFirstWidget.AddUObject(this, &UMainMenu::ReceiveOnInitFirstWidget);
	USideScrollerDelegates::OnShowWidget.AddUObject(this, &UMainMenu::ReceiveOnShowWidget);
	USideScrollerDelegates::OnShowHighscore.AddUObject(this, &UMainMenu::ReceiveOnShowHighscore);
	return true;
}

void UMainMenu::BindDelegates()
{
	USideScrollerDelegates::OnInitFirstWidget.AddUObject(this, &UMainMenu::ReceiveOnInitFirstWidget);
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

	FocusFirstWidget();
	return;
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

	FocusFirstWidget();
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

void UMainMenu::FocusFirstWidget()
{
	if (!IsValid(CurrentWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentWidget is not valid."));
		return;
	}

	UWidgetTree* WidgetTree = CurrentWidget->WidgetTree;
	USideScrollerWidget* SideScrollerWidget = Cast<USideScrollerWidget>(CurrentWidget);

	if (!IsValid(SideScrollerWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Cast failed. Current Widget is no SideScrollerWidget. Widget is %s"), *CurrentWidget->GetName());
		return;
	}

	UWidget* FirstSelected = WidgetTree->FindWidget(SideScrollerWidget->FirstSelectedWidget);

	if (!IsValid(FirstSelected))
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

	FirstSelected->SetUserFocus(PlayerController);
}

