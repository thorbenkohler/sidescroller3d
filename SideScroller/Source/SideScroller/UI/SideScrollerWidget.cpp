// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerWidget.h"
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
