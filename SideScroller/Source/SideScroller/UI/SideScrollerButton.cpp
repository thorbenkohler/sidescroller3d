// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerButton.h"

void USideScrollerButton::SlateHandleHovered()
{
    Super::SlateHandleHovered();

    FSlateBrush SlateBrush = WidgetStyle.Hovered;
    SetBackgroundColor(SlateBrush.TintColor.GetSpecifiedColor());
}

void USideScrollerButton::SlateHandleUnhovered()
{
    Super::SlateHandleUnhovered();

    FSlateBrush SlateBrush = WidgetStyle.Normal;
    SetBackgroundColor(SlateBrush.TintColor.GetSpecifiedColor());
}
