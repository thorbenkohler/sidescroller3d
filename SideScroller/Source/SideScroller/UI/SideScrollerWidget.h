// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SideScrollerWidget.generated.h"

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

	// Name of the first selected Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerWidget")
	FName FirstSelectedWidget;
};
