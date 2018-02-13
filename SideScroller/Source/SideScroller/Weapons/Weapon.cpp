// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "ProjectileSpawner.h"
#include "Character/SideScrollerCharacter.h"
#include "Projectiles/Projectile.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponForm"));
	SetRootComponent(StaticMeshComponent);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(StaticMeshComponent);

	FireButtonWasReleased = true;

	ProjectileSpawner = CreateDefaultSubobject<UProjectileSpawner>(TEXT("ProjectileSpawner"));
	AddInstanceComponent(ProjectileSpawner);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SideScrollerCharacter->IsValidLowLevel())
	{
		return;
	}

	// Spawning projectiles depending on the player's input
	FSideScrollerInput input = SideScrollerCharacter->GetCurrentInput();
	if (input.bFire && FireButtonWasReleased)
	{
		FireButtonWasReleased = false;
		FVector SpawnLocation = Muzzle->GetComponentLocation();
		FVector ShotDirection = SideScrollerCharacter->GetActorForwardVector();
		FRotator ShooterRotation = SideScrollerCharacter->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ProjectileSpawner->Spawn(ReferencedProjectile, SpawnLocation, ShooterRotation, SpawnInfo, ShotDirection);
	}

	if (!input.bFire)
	{
		FireButtonWasReleased = true;
	}
}

