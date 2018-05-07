// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CollectableHealth.generated.h"

UCLASS()
class SIDESCROLLER_API UCollectableHealth : public UActorComponent
{
    GENERATED_BODY()

public:
    // Gets triggered, when the actor collides with another actor
    UFUNCTION()
    void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

    // Gets added to the Players score
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CollectableHealth", meta = (AllowPrivateAccess = "true"))
    int32 Amount;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
};
