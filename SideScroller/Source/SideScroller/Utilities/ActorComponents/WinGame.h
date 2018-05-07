// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "WinGame.generated.h"

UCLASS()
class SIDESCROLLER_API UWinGame : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sends the according event
    UFUNCTION(BlueprintCallable, Category = "WinGame")
    void WinGame();
};
