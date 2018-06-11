// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Interfaces/ComboResettable.h"
#include "ComboReset.generated.h"

UCLASS(Blueprintable)
class SIDESCROLLER_API UComboReset : public UActorComponent
{
    GENERATED_BODY()

public:
    UComboReset();

    UFUNCTION(BlueprintNativeEvent, Category = "SideScroller")
    void Reset();
    void Reset_Implementation();

    UFUNCTION(BlueprintCallable, Category = "SideScroller")
    UActorComponent* GetResettableComponent();

private:
    void ReceiveOnCharacterLanded(const FHitResult& Hit);
};
