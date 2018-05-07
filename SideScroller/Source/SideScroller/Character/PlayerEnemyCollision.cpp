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
    SkeletalMeshComponent = Owner->FindComponentByClass<USkeletalMeshComponent>();
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
        UE_LOG(SideScrollerLog, Error, TEXT("%s SideScrollerCharacter has no SkeletalMeshComponent."), *LOG_STACK);
        return;
    }

    if (SkeletalMeshComponent->GetCollisionProfileName().IsEqual(NoCollisionWithEnemies))
    {
        return;
    }

    if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("%s SideScrollerCharacter is invalid."), *LOG_STACK);
        return;
    }

    ApplyGameplayEffect(Enemy);

    SideScrollerCharacter->EnemyCollidedWithPlayer();
}

void UPlayerEnemyCollision::ApplyGameplayEffect(AEnemy* Enemy)
{
    if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("SideScrollerCharacter is invalid in PlayerEnemyCollision."));
        return;
    }

    UAbilitySystemComponent* AbilitySystem = SideScrollerCharacter->AbilitySystem;

    if (!IsValid(Ability))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("%s no valid collision ability."), *LOG_STACK);
        return;
    }

    InstancedAbility = UAbilitySystemStatics::GetInstancedAbility(AbilitySystem, Ability.GetDefaultObject(),
                                                                  SideScrollerCharacter->Level);

    if (!IsValid(InstancedAbility))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("%s non valid InstancedAbility."), *LOG_STACK);
        return;
    }

    FGameplayAbilitySpecHandle Handle = InstancedAbility->GetCurrentAbilitySpecHandle();
    FGameplayAbilityActorInfo TempActorInfo = InstancedAbility->GetActorInfo();
    FGameplayAbilityActorInfo* ActorInfo = &TempActorInfo;
    FGameplayAbilityActivationInfo ActivationInfo = InstancedAbility->GetCurrentActivationInfo();

    if (!IsValid(Enemy->CollisionGameplayEffect))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("%s enemy %s has no GameplayEffect for collision referenced."), *LOG_STACK,
               *Enemy->GetName());
        return;
    }

    // Construct an impact game play effect spec and pass it to the projectile.
    FGameplayEffectSpecHandle ImpactEffect = InstancedAbility->MakeOutgoingGameplayEffectSpec(
        Handle, ActorInfo, ActivationInfo, Enemy->CollisionGameplayEffect,
        InstancedAbility->GetAbilityLevel(Handle, ActorInfo));

    AbilitySystem->ApplyGameplayEffectSpecToSelf(*ImpactEffect.Data.Get());
}
