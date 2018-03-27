// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "ProjectileSpawner.h"

// Sets default values
AWeapon::AWeapon()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponForm"));
    SetRootComponent(StaticMeshComponent);

    Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
    Muzzle->SetupAttachment(StaticMeshComponent);

    ProjectileSpawner = CreateDefaultSubobject<UProjectileSpawner>(TEXT("ProjectileSpawner"));
    AddInstanceComponent(ProjectileSpawner);
}

void AWeapon::OnDestroyedOwner(AActor* DestroyedActor)
{
    Destroy();
}

void AWeapon::BindDelegates()
{
    // crashes in BeginPlay()
    WeaponOwner->OnDestroyed.AddDynamic(this, &AWeapon::OnDestroyedOwner);
}
