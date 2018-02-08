// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Public/WorldCollision.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Weapon.h"
#include "Interfaces/DamageInterface.h"
#include "Components/ShapeComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Loc = GetActorLocation();
	FVector DesiredEndLoc = Loc + ((DeltaTime * Speed) * ShotDirection);

	FHitResult OutHit;
	if (UWorld* World = GetWorld())
	{
		FCollisionShape CollisionShape;
		//CollisionShape.SetCapsule(CapsuleRadius, CapsuleRadius * 2.0f);
		if (World->SweepSingleByProfile(OutHit, Loc, DesiredEndLoc, FQuat::Identity, CollisionProfile, CollisionShape))
		{
			SetActorLocation(OutHit.Location);
			if (IDamageInterface* DamageActor = Cast<IDamageInterface>(OutHit.Actor.Get()))
			{
				DamageActor->ReceiveDamage(Damage);
			}
			Destroy();
		}
		else
		{
			SetActorLocation(DesiredEndLoc);
		}
	}
}
