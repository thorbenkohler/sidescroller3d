// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerButton.h"
#include "Utilities/SideScrollerDelegates.h"


void USideScrollerButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USideScrollerButton::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
}

void USideScrollerButton::PostLoad()
{
	Super::PostLoad();
}

#if WITH_EDITOR
const FText USideScrollerButton::GetPaletteCategory()
{
	return Super::GetPaletteCategory();
}
#endif

UClass* USideScrollerButton::GetSlotClass() const
{
	return Super::GetSlotClass();
}

void USideScrollerButton::OnSlotAdded(UPanelSlot* Slot)
{
	Super::OnSlotAdded(Slot);
}

void USideScrollerButton::OnSlotRemoved(UPanelSlot* Slot)
{
	Super::OnSlotRemoved(Slot);
}

TSharedRef<SWidget> USideScrollerButton::RebuildWidget()
{
	return Super::RebuildWidget();
}

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
