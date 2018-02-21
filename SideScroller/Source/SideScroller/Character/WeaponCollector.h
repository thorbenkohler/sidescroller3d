// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collector.h"
#include "Components/ActorComponent.h"
#include "WeaponCollector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLER_API UWeaponCollector : public UCollector
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponCollector();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// To react to collisions with collectable weapons
	void ReceiveOnCollectableWeaponAdded(TSubclassOf<AActor> WeaponReference);

	// Spawns the referenced weapon
	void SpawnWeapon(UClass* ReferencedClass, FActorSpawnParameters SpawnParameters);

	// Spawns Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UWeaponSpawner* WeaponSpawner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
