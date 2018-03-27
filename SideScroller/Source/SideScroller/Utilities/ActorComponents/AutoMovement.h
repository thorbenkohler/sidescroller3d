// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AutoMovement.generated.h"

UCLASS(Blueprintable)
class SIDESCROLLER_API UAutoMovement : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AutoMovement")
    void Move(float TimeEllapsed, UStaticMeshComponent* StaticMeshComponent);

    UFUNCTION(BlueprintCallable, Category = "AutoMovement")
    void MoveFinished();

    UFUNCTION(BlueprintImplementableEvent, Category = "AutoMovement")
    void OnMove(float TimeEllapsed, UStaticMeshComponent* StaticMeshComponent);

    UFUNCTION(BlueprintImplementableEvent, Category = "AutoMovement")
    void OnMoveFinished();
};
