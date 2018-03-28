// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerWidget.h"

bool USideScrollerWidget::Initialize()
{
    bool Succesful = Super::Initialize();
    if (!Succesful)
    {
        return false;
    }

    return true;
}

bool USideScrollerWidget::InitializeWidget()
{
    CurrentWidget = this;

    CurrentWidget->AddToViewport();

    return true;
}

void USideScrollerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}
