// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utilities/SideScrollerDelegates.h"

bool USideScrollerWidget::Initialize()
{
	bool Succesful = Super::Initialize();
	if (!Succesful)
	{
		return false;
	}

	UWidgetTree* WidgetTree = this->WidgetTree;
	TArray<UWidget*> TempArray;
	WidgetTree->GetAllWidgets(TempArray);
	for (UWidget* Widget : TempArray)
	{
		USideScrollerButton* SideScrollerButton = Cast<USideScrollerButton>(Widget);
		if (IsValid(SideScrollerButton))
		{
			SideScrollerButton->WidgetStyle = ButtonStyle;
			AllButtons.Add(SideScrollerButton);
		}
	}

	return true;
}

bool USideScrollerWidget::InitializeMenu()
{
	if (!IsValid(this))
	{
		UE_LOG(LogTemp, Error, TEXT("There was a problem with the main menu creation."))
		return false;
	}
	CurrentWidget = this;

	CurrentWidget->AddToViewport();

	return true;
}

void USideScrollerWidget::WidgetTick(FGeometry MyGeometry, float InDeltaTime)
{
	for (USideScrollerButton* SideScrollerButton : AllButtons)
	{
		if (SideScrollerButton->HasKeyboardFocus())
		{
			SideScrollerButton->SlateHandleHovered();
			continue;
		}
		SideScrollerButton->SlateHandleUnhovered();
	}
}

void USideScrollerWidget::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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


