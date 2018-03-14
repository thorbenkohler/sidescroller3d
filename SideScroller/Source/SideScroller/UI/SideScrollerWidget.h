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

	// Used to initialize elements after menu is shown
	virtual bool InitializeMenu();

	// Controls hovering
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Remove the current menu widget and create a new one from the specified class, if provided.
	UFUNCTION(BlueprintCallable, Category = "SideScrollerWidget")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	// Caches of SideScroller Buttons
	TArray<USideScrollerButton*> AllButtons;

	// Used to define a style for all buttons in this menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerWidget")
	FButtonStyle ButtonStyle;

	// The current active menu
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerWidget")
	UUserWidget* CurrentWidget;
};
