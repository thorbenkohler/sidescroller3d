// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerEnemyCollision.h"
#include "Enemies/Enemy.h"

// Called when the game starts
void UPlayerEnemyCollision::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    Owner->OnActorBeginOverlap.AddDynamic(this, &UPlayerEnemyCollision::ActorBeginOverlap);

    SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

    if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Cast to SideScrollerCharacter failed."));
		return;
    }

    SkeletalMeshComponent = Owner->FindComponentByClass<USkeletalMeshComponent>();

    if (!IsValid(SkeletalMeshComponent))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("In PlayerEnemyCollision character has no SkeletalMeshComponent."));
        return;
    }
}

void UPlayerEnemyCollision::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    // Check if the colliding actor was an enemy
    AEnemy* Enemy = Cast<AEnemy>(OtherActor);

    if (!IsValid(Enemy))
    {
        return;
    }

	if (!IsValid(SkeletalMeshComponent))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("In PlayerEnemyCollision character has no SkeletalMeshComponent."));
		return;
	}

    if (SkeletalMeshComponent->GetCollisionProfileName().IsEqual(NoCollisionWithEnemies))
    {
        return;
    }

    if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("SideScrollerCharacter is invalid in PlayerEnemyCollision."));
		return;
    }

    SideScrollerCharacter->DamageTaken(Enemy->DamageOnTouch);
    SideScrollerCharacter->EnemyCollidedWithPlayer();
}
