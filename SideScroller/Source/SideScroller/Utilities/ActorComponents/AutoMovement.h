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
    void Move(UStaticMeshComponent* StaticMeshComponent);

    UFUNCTION(BlueprintCallable, Category = "AutoMovement")
    void MoveFinished();

    UFUNCTION(BlueprintImplementableEvent, Category = "AutoMovement")
    void OnMove(UStaticMeshComponent* StaticMeshComponent);

    UFUNCTION(BlueprintImplementableEvent, Category = "AutoMovement")
    void OnMoveFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoMovement")
	float InitialDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoMovement")
	float TimeToReachDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoMovement")
	float WaitBeforeTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoMovement")
	FVector RelativeDestination;
};
