// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerWidget.h"
#include "Runtime/SlateCore/Public/Styling/SlateTypes.h"
#include "SideScrollerMenuWidget.generated.h"

UCLASS()
class SIDESCROLLER_API USideScrollerMenuWidget : public USideScrollerWidget
{
	GENERATED_BODY()

public:
	// Replacing BeginPlay() for widgets
	virtual bool Initialize() override;

	// Controls hovering
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Remove the current menu widget and create a new one from the specified class, if provided.
	UFUNCTION(BlueprintCallable, Category = "SideScrollerWidget")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	// Used to show widgets additionally
	UFUNCTION(BlueprintCallable, Category = "SideScrollerWidget")
	void ShowNewWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	// Caches SideScroller Buttons
	TArray<class USideScrollerButton*> AllButtons;

	// Used to define a style for all buttons in this menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerWidget")
	FButtonStyle ButtonStyle;
};
