// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyWeapon.h"
#include "ProjectileSpawner.h"
#include "Enemies/Enemy.h"


// Called when the game starts or when spawned
void AEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();

	DeltaCooldown = Cooldown;
}
