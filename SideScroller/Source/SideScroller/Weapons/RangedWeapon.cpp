// Fill out your copyright notice in the Description page of Project Settings.

#include "RangedWeapon.h"
#include "ProjectileSpawner.h"

// Sets default values
ARangedWeapon::ARangedWeapon()
{
    Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
    Muzzle->SetupAttachment(StaticMeshComponent);

    ProjectileSpawner = CreateDefaultSubobject<UProjectileSpawner>(TEXT("ProjectileSpawner"));
    AddInstanceComponent(ProjectileSpawner);
}
