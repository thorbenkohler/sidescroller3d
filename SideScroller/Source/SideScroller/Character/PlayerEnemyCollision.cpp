// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerEnemyCollision.h"
#include "SideScrollerCharacter.h"
#include "Enemies/Enemy.h"
#include "Utilities/SideScrollerDelegates.h"


// Called when the game starts
void UPlayerEnemyCollision::BeginPlay()
{
	Super::BeginPlay();

	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!IsValid(PrimitiveComponent))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("No primitive component found in %p"), this);
		return;
	}

	PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UPlayerEnemyCollision::OnOverlapBegin);
}

void UPlayerEnemyCollision::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the colliding actor was an enemy
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);

	if (!IsValid(Enemy))
	{
		return;
	}

	ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(GetOwner());

	if (!IsValid(SideScrollerCharacter))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Cast to SideScrollerCharacter failed."));
		return;
	}

	SideScrollerCharacter->DamageTaken(Enemy->DamageOnTouch);
	SideScrollerCharacter->EnemyCollidedWithPlayer();
}
