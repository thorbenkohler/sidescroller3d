// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "EnemyWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API AEnemyWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Destroys the weapon if its owner gets destroyed
	UFUNCTION()
	void OnDestroyedOwner(AActor* DestroyedActor);

	// Binds delegates, depending on the ParentActor
	virtual void BindDelegates() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
