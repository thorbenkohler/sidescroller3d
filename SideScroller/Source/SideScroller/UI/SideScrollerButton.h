// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Input/Reply.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SWidget.h"
#include "Components/ContentWidget.h"
#include "Components/Button.h"

#include "SideScrollerButton.generated.h"

class SButton;
class USlateWidgetStyleAsset;

UCLASS()
class SIDESCROLLER_API USideScrollerButton : public UButton
{
	GENERATED_BODY()

public:
	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

	// Used to show hovered visuals
	void SlateHandleHovered();

	// Used to show unhovered visuals
	void SlateHandleUnhovered();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:

	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
	// End UPanelWidget

	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
#if WITH_EDITOR
	virtual TSharedRef<SWidget> RebuildDesignWidget(TSharedRef<SWidget> Content) override { return Content; }
#endif
	//~ End UWidget Interface

};
