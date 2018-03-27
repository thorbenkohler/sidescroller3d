// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "WeaponSpawner.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDESCROLLER_API UWeaponSpawner : public UActorComponent
{
    GENERATED_BODY()

public:
    // Spawns the referenced weapon
    AWeapon* Spawn(TSubclassOf<AActor> ReferencedClass);
};
