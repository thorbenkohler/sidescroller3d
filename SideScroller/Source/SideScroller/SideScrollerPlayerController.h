// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SideScrollerPlayerController.generated.h"

/**
*
*/
UCLASS()
class SIDESCROLLER_API ASideScrollerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
