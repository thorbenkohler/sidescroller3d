// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Weapons/Weapon.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	WeaponSpawner = CreateDefaultSubobject<UWeaponSpawner>(TEXT("WeaponSpawner"));
	AddInstanceComponent(WeaponSpawner);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//if (!ReferencedWeapon->IsValidLowLevel())
	//{
	//	return;
	//}

	//WeaponSpawner->Spawn(ReferencedWeapon);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::ReceiveDamage(int32 IncomingDamage)
{
	if (IncomingDamage >= Health)
	{
		if (Health >= 0)
		{
			Health = -1;
			Die();
		}
		return;
	}
	Health -= IncomingDamage;
}

int32 AEnemy::GetHealthRemaining()
{
	return Health;
}
