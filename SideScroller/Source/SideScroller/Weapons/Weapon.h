// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Utilities/InputEnums.h"
#include "Weapon.generated.h"

UCLASS()
class SIDESCROLLER_API AWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWeapon();

    // Binds delegates, depending on the ParentActor
    virtual void BindDelegates();

    // Destroys the weapon if its owner gets destroyed
    UFUNCTION()
    virtual void OnDestroyedOwner(AActor* DestroyedActor);

    // Sets the actual form for the weapon
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    UStaticMeshComponent* StaticMeshComponent;

    // Used for shoot direction
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    AActor* WeaponOwner;

    // The ability this weapon triggers
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<class UGameplayAbility> Ability;

	// The socket this weapon is used
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName UnsheatedSocketName;

	// The socket this weapon is not used, but carried
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName SheatedSocketName;

	// The slot this weapon gets set to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EAbilityInput AbilitySlot;
};
