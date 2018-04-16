// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API AMeleeWeapon : public AWeapon
{
    GENERATED_BODY()

public:
    AMeleeWeapon();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee")
	int32 Damage;
};
