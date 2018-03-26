// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "SideScrollerButton.generated.h"

class SButton;
class USlateWidgetStyleAsset;

UCLASS()
class SIDESCROLLER_API USideScrollerButton : public UButton
{
	GENERATED_BODY()

public:
	// Used to show hovered visuals
	void SlateHandleHovered();

	// Used to show unhovered visuals
	void SlateHandleUnhovered();
};
