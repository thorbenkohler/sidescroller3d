// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ProjectileSpawner.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDESCROLLER_API UProjectileSpawner : public UActorComponent
{
    GENERATED_BODY()

public:
    // Used to spawn projectiles
    void Spawn(TSubclassOf<AActor> ReferencedProjectileClass, FVector& SpawnLocation, FRotator& ShooterRotation,
               FActorSpawnParameters& SpawnParameters, const FVector& ShotDirection);
};
