// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"

#include "Interfaces/DamageInterface.h"
#include "Interfaces/HealthInterface.h"

#include "GameFramework/Pawn.h"

#include "Abilities/AttributeSets/HealthAttributeSet.h"

#include "Enemy.generated.h"

UCLASS()
class SIDESCROLLER_API AEnemy : public APawn, public IAbilitySystemInterface, public IHealthInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AEnemy();

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Destroys the enemy and can used for special effects
    UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
    void OnDeath() const override;

    // If the enemy gets hit by anthing, cues can be spawned here
    UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
    void OnImpact();

    UAbilitySystemComponent* GetAbilitySystemComponent() const override
    {
        return Cast<UAbilitySystemComponent>(AbilitySystem);
    };

    UHealthComponent* GetHealthComponent() const override
    {
        return HealthComponent;
    };

    // Sets the actual form for the enemy
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    UStaticMeshComponent* StaticMeshComponent;

    // Manages damage and adding health
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
    class UHealthComponent* HealthComponent;

    // Ability System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
    class USideScrollerAbilitySystemComponent* AbilitySystem;

    // Defines the enemie's health amount
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
    const UHealthAttributeSet* HealthAttributeSet;

    // Triggers the ability if the player collides with the player
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
    TSubclassOf<class UGameplayEffect> CollisionGameplayEffect;
};
