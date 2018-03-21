// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTask_SpawnProjectile.h"



UAbilityTask_SpawnProjectile::UAbilityTask_SpawnProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAbilityTask_SpawnProjectile* UAbilityTask_SpawnProjectile::CreateMyTask(UGameplayAbility* OwningAbility, FName TaskInstanceName, float ExampleVariable)
{

	UAbilityTask_SpawnProjectile* AbilityTask_SpawnProjectile = NewAbilityTask<UAbilityTask_SpawnProjectile>(OwningAbility, TaskInstanceName);
	return AbilityTask_SpawnProjectile;
}

void UAbilityTask_SpawnProjectile::Activate()
{
	//FVector SpawnLocation = Muzzle->GetComponentLocation();
	//FRotator ShooterRotation = SideScrollerCharacter->GetActorRotation();
	//UE_LOG(LogTemp, Log, TEXT("Spawn Projectile successfully activated %s"), *GetOwner()->GetName());
}

UAbilityTask_SpawnProjectile* UAbilityTask_SpawnProjectile::SpawnActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> InClass)
{
	UAbilityTask_SpawnProjectile* MyObj = NewAbilityTask<UAbilityTask_SpawnProjectile>(OwningAbility);
	MyObj->CachedTargetDataHandle = MoveTemp(TargetData);
	return MyObj;
}

// ---------------------------------------------------------------------------------------

bool UAbilityTask_SpawnProjectile::BeginSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> InClass, AActor*& SpawnedActor)
{
	if (Ability && Ability->GetCurrentActorInfo()->IsNetAuthority() && ShouldBroadcastAbilityTaskDelegates())
	{
		UWorld* const World = GEngine->GetWorldFromContextObject(OwningAbility, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{
			SpawnedActor = World->SpawnActorDeferred<AActor>(InClass, FTransform::Identity, NULL, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
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

void UAbilityTask_SpawnProjectile::FinishSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, AActor* SpawnedActor)
{
	if (SpawnedActor)
	{
		bool bTransformSet = false;
		FTransform SpawnTransform;
		if (FGameplayAbilityTargetData* LocationData = CachedTargetDataHandle.Get(0))		//Hardcode to use data 0. It's OK if data isn't useful/valid.
		{
			//Set location. Rotation is unaffected.
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

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			Success.Broadcast(SpawnedActor);
		}
	}

	EndTask();
}

// --------------------------------------------------------------------------------------