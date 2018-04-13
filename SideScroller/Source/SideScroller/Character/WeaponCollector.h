// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Collector.h"
#include "WeaponCollector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponCollected, AWeapon*, Weapon);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDESCROLLER_API UWeaponCollector : public UCollector
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UWeaponCollector();

    // To react to collisions with collectable weapons
    void ReceiveOnCollectableWeaponAdded(TSubclassOf<AActor> WeaponReference);

    // Spawns the referenced weapon
    void SpawnWeapon(UClass* ReferencedClass, FActorSpawnParameters SpawnParameters);

	// Used to set the weapon to the socket
	UPROPERTY(BlueprintAssignable, Category = "WeaponCollector")
	FOnWeaponCollected OnWeaponCollected;

    // Spawns Weapons
    class UWeaponSpawner* WeaponSpawner;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponCollector")
    class ARangedWeapon* CurrentlyEquippedRangedWeapon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponCollector")
    class AMeleeWeapon* CurrentlyEquippedMeleeWeapon;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
};
