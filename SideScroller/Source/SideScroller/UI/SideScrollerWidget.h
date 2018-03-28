// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "SideScrollerWidget.generated.h"


UCLASS()
class SIDESCROLLER_API USideScrollerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Widget replacement for BeginPlay()
	bool Initialize();

	// Used to initialize elements after menu is shown
	virtual bool InitializeWidget();

	// Controls hovering
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// The current active menu
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerWidget")
	UUserWidget* CurrentWidget;
};
