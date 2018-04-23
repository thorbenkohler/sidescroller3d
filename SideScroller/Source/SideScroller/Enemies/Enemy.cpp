// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    AbilitySystem = CreateDefaultSubobject<USideScrollerAbilitySystemComponent>(TEXT("AbilitySystem"));
    HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("AttributeSet"));
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::DamageTaken(int32 IncomingDamage)
{
    if (IncomingDamage >= Health)
    {
        if (Health >= 0)
        {
            Health = -1;
            OnDeath();
        }
        return;
    }
    Health -= IncomingDamage;
    Impact();
}
