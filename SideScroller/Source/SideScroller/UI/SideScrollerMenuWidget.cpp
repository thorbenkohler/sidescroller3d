// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerMenuWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetTree.h"

bool USideScrollerMenuWidget::Initialize()
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

void USideScrollerMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

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

void USideScrollerMenuWidget::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (IsValid(CurrentWidget))
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }

	ShowNewWidget(NewWidgetClass);
}

void USideScrollerMenuWidget::ShowNewWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (!IsValid(NewWidgetClass))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("NewWidgetClass is not valid."));
        return;
    }

    CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

    if (!IsValid(CurrentWidget))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Creating a new widget failed."));
        return;
    }

    CurrentWidget->AddToViewport();
}
