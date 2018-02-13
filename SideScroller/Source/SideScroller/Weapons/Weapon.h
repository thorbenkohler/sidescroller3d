// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Muzzle.h"
#include "Weapon.generated.h"

// TODO: Good or bad practice?
class ASideScrollerCharacter;
class UProjectileSpawner;

UCLASS()
class SIDESCROLLER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the actual form for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	UStaticMeshComponent* StaticMeshComponent;

	// Sets the actual form for the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	ASideScrollerCharacter* SideScrollerCharacter;

	// Sets the actual form for the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AActor* OwningActor;

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
	UProjectileSpawner* ProjectileSpawner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool FireButtonWasReleased;
};
