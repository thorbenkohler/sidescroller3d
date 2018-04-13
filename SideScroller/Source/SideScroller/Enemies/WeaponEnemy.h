// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "Enemies/Enemy.h"
#include "WeaponEnemy.generated.h"

UCLASS()
class SIDESCROLLER_API AWeaponEnemy : public AEnemy
{
    GENERATED_BODY()

public:
    AWeaponEnemy();

    virtual void BeginPlay() override;

    // Used to trigger the ability of this enemy
    UFUNCTION(BlueprintCallable, Category = "WeaponEnemy")
    void ActivateAbility();

    // Reference to the blueprint of the weapon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponEnemy")
    TSubclassOf<AActor> ReferencedWeapon;

    // Spawns a weapon if one is referenced
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponEnemy")
    class UWeaponSpawner* WeaponSpawner;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponEnemy")
    ARangedWeapon* CurrentlyEquippedRangedWeapon;

    // Used to cache the ability after initalizing it
    UGameplayAbility* InstancedAbility;
};
