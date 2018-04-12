// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "Muzzle.h"
#include "RangedWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API ARangedWeapon : public AWeapon
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ARangedWeapon();

    // Blueprint Asset which is spawned when shooting.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ranged")
    TSubclassOf<AActor> ReferencedProjectile;

    // Position to spawn the projectiles.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged")
    USceneComponent* Muzzle;

    // Spawns projectiles
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged")
    class UProjectileSpawner* ProjectileSpawner;
};
