// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SideScrollerWidget.generated.h"

class USideScrollerButton;

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API USideScrollerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Widget replacement for BeginPlay()
	bool Initialize();

	// Gets called in Blueprint by the Tick() event
	UFUNCTION(BlueprintCallable, Category = "SideScrollerWidget")
	virtual void WidgetTick(FGeometry MyGeometry, float InDeltaTime);

	// Caches of SideScroller Buttons
	TArray<USideScrollerButton*> AllButtons;

	// Used to define a style for all buttons in this menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerWidget")
	FButtonStyle ButtonStyle;
};
