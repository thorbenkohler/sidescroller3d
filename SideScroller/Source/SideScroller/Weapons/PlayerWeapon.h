// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class SIDESCROLLER_API APlayerWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the actual form for the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerWeapon")
	class ASideScrollerCharacter* SideScrollerCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Used to force the player to press the button anew
	bool FireButtonWasReleased;
};
