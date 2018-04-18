// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API AMeleeWeapon : public AWeapon
{
    GENERATED_BODY()

public:
	// Triggers when another actor overlaps
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	// Inflict on contact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee")
	int32 Damage;

protected:
	virtual void BeginPlay() override;
};
