// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerEnemyCollision.h"
#include "SideScrollerCharacter.h"
#include "Enemies/Enemy.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UPlayerEnemyCollision::UPlayerEnemyCollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

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

// Called every frame
void UPlayerEnemyCollision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
