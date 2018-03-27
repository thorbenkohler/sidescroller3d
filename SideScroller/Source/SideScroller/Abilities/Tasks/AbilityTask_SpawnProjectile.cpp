// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTask_SpawnProjectile.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "SideScroller.h"
#include "Weapons/Muzzle.h"
#include "Weapons/Weapon.h"
#include "Character/WeaponCollector.h"
#include "Enemies/WeaponEnemy.h"
#include "AbilitySystemComponent.h"

UAbilityTask_SpawnProjectile* UAbilityTask_SpawnProjectile::SpawnActor(UGameplayAbility* OwningAbility,
                                                                       FGameplayAbilityTargetDataHandle TargetData,
                                                                       TSubclassOf<AActor> InClass)
{
    if (!IsValid(OwningAbility))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("OwningAbility is not valid."));
        return nullptr;
    }

    UAbilityTask_SpawnProjectile* MyObj = NewAbilityTask<UAbilityTask_SpawnProjectile>(OwningAbility);
    MyObj->CachedTargetDataHandle = MoveTemp(TargetData);
    return MyObj;
}

// ---------------------------------------------------------------------------------------

bool UAbilityTask_SpawnProjectile::BeginSpawningActor(UGameplayAbility* OwningAbility,
                                                      FGameplayAbilityTargetDataHandle TargetData,
                                                      TSubclassOf<AActor> InClass, AActor*& SpawnedActor)
{
    if (!IsValid(OwningAbility))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("OwningAbility is not valid."));
        return false;
    }

    if (Ability && Ability->GetCurrentActorInfo()->IsNetAuthority()) // && ShouldBroadcastAbilityTaskDelegates())
    {
        UWorld* const World = GEngine->GetWorldFromContextObject(OwningAbility, EGetWorldErrorMode::LogAndReturnNull);
        if (World)
        {
            SpawnPosition = GetProjectilePosition(OwningAbility);
            SpawnedActor = World->SpawnActorDeferred<AActor>(InClass, FTransform::Identity, NULL, NULL,
                                                             ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
        }
    }

    if (SpawnedActor == nullptr)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast(nullptr);
        }
        return false;
    }

    return true;
}

void UAbilityTask_SpawnProjectile::FinishSpawningActor(UGameplayAbility* OwningAbility,
                                                       FGameplayAbilityTargetDataHandle TargetData,
                                                       AActor* SpawnedActor)
{
    if (SpawnedActor)
    {
        bool bTransformSet = false;
        FTransform SpawnTransform;
        if (FGameplayAbilityTargetData* LocationData =
                CachedTargetDataHandle.Get(0)) // Hardcode to use data 0. It's OK if data isn't useful/valid.
        {
            // Set location. Rotation is unaffected.
            if (LocationData->HasHitResult())
            {
                SpawnTransform.SetLocation(LocationData->GetHitResult()->Location);
                bTransformSet = true;
            }
            else if (LocationData->HasEndPoint())
            {
                SpawnTransform = LocationData->GetEndPointTransform();
                bTransformSet = true;
            }
        }
        if (!bTransformSet)
        {
            SpawnTransform = AbilitySystemComponent->GetOwner()->GetTransform();
        }

        SpawnedActor->FinishSpawning(SpawnTransform);

        SpawnedActor->SetActorLocation(SpawnPosition);

        if (ShouldBroadcastAbilityTaskDelegates())
        {
            Success.Broadcast(SpawnedActor);
        }
    }

    EndTask();
}

// --------------------------------------------------------------------------------------

FVector UAbilityTask_SpawnProjectile::GetProjectilePosition(UGameplayAbility* OwningAbility)
{
    if (!IsValid(OwningAbility))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("OwningAbility is not valid."));
        return FVector::ZeroVector;
    }

    AActor* AbilityOwner = OwningAbility->GetOwningActorFromActorInfo();

    if (!IsValid(AbilityOwner))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("AbilityOwner is not valid."));
        return FVector::ZeroVector;
    }

    ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(AbilityOwner);
    AWeapon* Weapon;

    if (!IsValid(SideScrollerCharacter))
    {
        AWeaponEnemy* WeaponEnemy = Cast<AWeaponEnemy>(AbilityOwner);

        if (!IsValid(WeaponEnemy))
        {
            UE_LOG(SideScrollerLog, Error,
                   TEXT("Cast failed. AbilityOwner is neither of type ASideScrollerCharacter nor AWeaponEnemy."));
            return FVector::ZeroVector;
        }

        Weapon = WeaponEnemy->LastSpawnedWeapon;
    }
    else
    {
        UWeaponCollector* WeaponCollector = SideScrollerCharacter->WeaponCollector;

        if (!IsValid(WeaponCollector))
        {
            UE_LOG(SideScrollerLog, Error, TEXT("WeaponCollector is not valid."));
            return FVector::ZeroVector;
        }

        Weapon = WeaponCollector->LastSpawnedWeapon;
    }

    if (!IsValid(Weapon))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Weapon is not valid."));
        return FVector::ZeroVector;
    }

    USceneComponent* Muzzle = Weapon->Muzzle;

    if (!IsValid(Muzzle))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Muzzle is not valid."));
        return FVector::ZeroVector;
    }

    return Muzzle->GetComponentLocation();
}
