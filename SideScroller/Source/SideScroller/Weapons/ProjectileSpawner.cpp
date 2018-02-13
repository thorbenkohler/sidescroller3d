// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileSpawner.h"
#include "Projectiles/Projectile.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UProjectileSpawner::UProjectileSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UProjectileSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UProjectileSpawner::Spawn(TSubclassOf<AActor> ReferencedProjectileClass, FVector &SpawnLocation, FRotator &ShooterRotation, FActorSpawnParameters &SpawnInfo, const FVector &ShotDirection)
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ReferencedProjectileClass, SpawnLocation, ShooterRotation, SpawnInfo);

	FRotator ProjectileRotation = Projectile->GetActorRotation();

	// The character starts with a 90 degree offset
	ProjectileRotation.Yaw = ShooterRotation.Yaw - 90.0f;
	Projectile->SetActorRelativeRotation(ProjectileRotation);
	Projectile->ShotDirection = ShotDirection;
}
