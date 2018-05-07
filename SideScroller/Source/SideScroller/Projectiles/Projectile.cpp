// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Interfaces/HealthInterface.h"

#include "Components/ShapeComponent.h"

#include "Runtime/Engine/Public/WorldCollision.h"

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

    if (Speed <= 0)
    {
        TimeUntilDestruction = 0;
        UE_LOG(SideScrollerLog, Warning, TEXT("Projectile has no speed and gets therefore destroyed immediately"));
        return;
    }
    TimeUntilDestruction = TravelDistance / Speed;
	ShotDirection = GetActorForwardVector().RotateAngleAxis(90.0f, FVector::UpVector);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector Loc = GetActorLocation();

    FVector DesiredEndLoc = Loc + ((DeltaTime * Speed) * ShotDirection);
    TimeTraveled += DeltaTime;
    if (TimeTraveled > TimeUntilDestruction)
    {
        Destroy();
        return;
    }

    FHitResult OutHit;
    if (UWorld* World = GetWorld())
    {
        FCollisionShape CollisionShape;
        if (World->SweepSingleByProfile(OutHit, Loc, DesiredEndLoc, FQuat::Identity, CollisionProfile, CollisionShape))
        {
            SetActorLocation(OutHit.Location);
			AActor* TempActor = OutHit.Actor.Get();
            if (IHealthInterface* DamageActor = Cast<IHealthInterface>(TempActor))
            {
				UAbilitySystemComponent* AbilitySystemComponent =
					UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TempActor);

				if (IsValid(AbilitySystemComponent) && ImpactEffect.IsValid())
				{
					AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*ImpactEffect.Data.Get());
				}
			}
            Destroy();
        }
        else
        {
            SetActorLocation(DesiredEndLoc);
        }
    }
}
