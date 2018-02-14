// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyWeapon.h"
#include "ProjectileSpawner.h"
#include "Projectiles/Projectile.h"
#include "Enemies/Enemy.h"


// Sets default values
AEnemyWeapon::AEnemyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();

	DeltaCooldown = Cooldown;
}

// Called every frame
void AEnemyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(WeaponOwner))
	{
		return;
	}

	if (DeltaCooldown > 0)
	{
		DeltaCooldown -= DeltaTime;
		return;
	}
	DeltaCooldown = Cooldown;

	FVector SpawnLocation = Muzzle->GetComponentLocation();
	FVector ShotDirection = WeaponOwner->GetActorForwardVector();
	FRotator ShooterRotation = WeaponOwner->GetActorRotation();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ProjectileSpawner->Spawn(ReferencedProjectile, SpawnLocation, ShooterRotation, SpawnParameters, ShotDirection);
}

