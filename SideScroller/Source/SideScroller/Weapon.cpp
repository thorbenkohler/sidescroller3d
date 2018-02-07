// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Projectile.h"


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
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	const FSoftObjectPath& AssetPath = ReferencedProjectile.ToSoftObjectPath();
	UBlueprint* newBp = LoadObject<UBlueprint>(nullptr, *AssetPath.ToString());

	if (!newBp->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Loading projectile failed"));
		return;
	}

	ReferencedProjectileClass = newBp->GeneratedClass;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SideScrollerCharacter->IsValidLowLevel())
	{
		return;
	}

	FSideScrollerInput input = SideScrollerCharacter->GetCurrentInput();
	if (input.bFire && FireButtonWasReleased)
	{
		FireButtonWasReleased = false;
		FVector SpawnLocation = Muzzle->GetComponentLocation();
		FVector ShotDirection = SideScrollerCharacter->GetActorForwardVector();
		FRotator ShooterRotation = SideScrollerCharacter->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ReferencedProjectileClass, SpawnLocation, ShooterRotation, SpawnInfo);

		FRotator ProjectileRotation = Projectile->GetActorRotation();

		// The character starts with a 90 degree offset
		ProjectileRotation.Yaw = ShooterRotation.Yaw - 90.0f;
		Projectile->SetActorRelativeRotation(ProjectileRotation);
		Projectile->ShotDirection = ShotDirection;
	}

	if (!input.bFire)
	{
		FireButtonWasReleased = true;
	}
}
