// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/DamageInterface.h"
#include "AbilitySystemInterface.h"
#include "Enemy.generated.h"

UCLASS()
class SIDESCROLLER_API AEnemy : public APawn, public IDamageInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//~ Begin IDamageInterface
	virtual void DamageTaken(int32 IncomingDamage) override;
	//~ End IDamageInterface

	// Destroys the enemy and can used for special effects
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void OnDeath();

	// Destroys the enemy and can used for special effects
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void Impact();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };

	// Sets the actual form for the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMeshComponent* StaticMeshComponent;
	 
	// Current health value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "0.0"))
	int32 Health;

	// The amount of damage that is dealt on touch
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "0.0"))
	int32 DamageOnTouch;

	// Ability System
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

};
