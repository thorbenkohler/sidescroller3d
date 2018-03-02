// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"
#include "ProjectileSpawner.h"
#include "Character/SideScrollerCharacter.h"


// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FireButtonWasReleased = true;
}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(SideScrollerCharacter))
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
		ShotFired();
	}

	if (!input.bFire)
	{
		FireButtonWasReleased = true;
	}
}

void APlayerWeapon::OnDestroyedOwner(AActor* DestroyedActor)
{
	Destroy();
}

void APlayerWeapon::BindDelegates()
{
	Super::BindDelegates();

	WeaponOwner->OnDestroyed.AddDynamic(this, &APlayerWeapon::OnDestroyedOwner);
}
