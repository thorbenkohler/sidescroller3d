// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/Actor.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilityTask_SpawnProjectile.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnProjectileDelegate, AActor*, SpawnedActor);


UCLASS()
class SIDESCROLLER_API UAbilityTask_SpawnProjectile : public UAbilityTask
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FSpawnProjectileDelegate Success;

	/** Called when we can't spawn: on clients or potentially on server if they fail to spawn (rare) */
	UPROPERTY(BlueprintAssignable)
	FSpawnProjectileDelegate DidNotSpawn;
	
	/** Spawn new Projectile on the network authority (server) */
	UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category="Ability|Tasks")
	static UAbilityTask_SpawnProjectile* SpawnActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> Class);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")
	bool BeginSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> Class, AActor*& SpawnedActor);


	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")
	void FinishSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, AActor* SpawnedActor);

protected:
	FGameplayAbilityTargetDataHandle CachedTargetDataHandle;

private:
	// Retrieves position via the ability owner, in this case the player character
	FVector GetProjectilePosition(UGameplayAbility* OwningAbility);

	// Retrieves the referenced projectile of the weapon
	TSubclassOf<AActor> GetProjectileClass(UGameplayAbility* OwningAbility);

	// Retrieves the corresponding weapon. Serves as convenience method
	class ARangedWeapon* GetRangedWeapon(UGameplayAbility* OwningAbility);

	// Location needs to be set in FinishSpawningActor where no reference to 
	// the OwningAbility is left, so this needs to be cached in BeginSpawningActor
	FVector SpawnPosition;
};
