// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Muzzle.h"
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

	// Blueprint Asset which is spawned when shooting.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AActor> ReferencedProjectile;

	// How fast the gun might shoot.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Cooldown;

	// Position to spawn the projectiles.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USceneComponent* Muzzle;

	// Set the distance from weapon to character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector Offset;

	// Spawns projectiles
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UProjectileSpawner* ProjectileSpawner;

	// Used for shoot direction
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AActor* WeaponOwner;

	// The ability this weapon triggers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerWeapon")
	TSubclassOf<class UGameplayAbility> Ability;

protected:
	// Temporary value for the cooldown.
	float DeltaCooldown;
};
