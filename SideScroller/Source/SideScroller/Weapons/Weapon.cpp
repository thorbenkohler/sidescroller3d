// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponForm"));
    SetRootComponent(StaticMeshComponent);
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
