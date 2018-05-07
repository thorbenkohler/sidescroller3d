// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerEnemyCollision.generated.h"


UCLASS()
class SIDESCROLLER_API UPlayerEnemyCollision : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerEnemyCollision")
	FName NoCollisionWithEnemies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerEnemyCollision")
	TSubclassOf<UGameplayAbility> Ability;

private:
	// Cached instance from Owner
	class USkeletalMeshComponent* SkeletalMeshComponent;

	// Cached instance from Owner
	class ASideScrollerCharacter* SideScrollerCharacter;

	// To calculate the damage if an enemy collides
	void ApplyGameplayEffect(class AEnemy* Enemy);

public:
	// Used to collide with enemies
	class UGameplayAbility* InstancedAbility;
};
