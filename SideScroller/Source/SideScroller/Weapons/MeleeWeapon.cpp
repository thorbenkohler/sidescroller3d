// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeWeapon.h"
#include "Abilities/Utilities/AbilityDelegates.h"

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnOverlapBegin);
}

void AMeleeWeapon::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// Check if the colliding actor was an enemy
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);

	if (!IsValid(Enemy))
	{
		return;
	}

	UAbilityDelegates::OnDashOverlapBegin.Broadcast(OtherActor);
}
