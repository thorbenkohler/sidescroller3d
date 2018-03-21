// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "ProjectileSpawner.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponForm"));
	SetRootComponent(StaticMeshComponent);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(StaticMeshComponent);

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
