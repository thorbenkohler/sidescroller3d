// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the actual form for the projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	// Describes what this projectile hits.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName CollisionProfile;

	// How fast the projectile files. In Vector units per Second.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed;

	// How hard this projectile hits.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	int32 Damage;

	// The direction, the actor was looking when shooting.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	FVector ShotDirection;

	// The time until the projectile gets destroyed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	float TimeUntilDestruction;

	// How far the projectile flies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float TravelDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Used to decide when the projectile can be destroyed.
	float TimeTraveled;
};
