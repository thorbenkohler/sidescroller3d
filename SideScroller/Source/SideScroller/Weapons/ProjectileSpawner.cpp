// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileSpawner.h"
#include "Projectiles/Projectile.h"

void UProjectileSpawner::Spawn(TSubclassOf<AActor> ReferencedProjectileClass, FVector& SpawnLocation,
                               FRotator& ShooterRotation, FActorSpawnParameters& SpawnParameters,
                               const FVector& ShotDirection)
{
    AProjectile* Projectile =
        GetWorld()->SpawnActor<AProjectile>(ReferencedProjectileClass, SpawnLocation, ShooterRotation, SpawnParameters);

    if (!IsValid(Projectile))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Spawning projectile failed."));
        return;
    }
}
