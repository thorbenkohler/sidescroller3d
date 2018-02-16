// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/DamageInterface.h"
#include "GameFramework/Character.h"
#include "SideScrollerCharacter.generated.h"


// This struct covers all possible sideScroller input schemes.
USTRUCT(BlueprintType)
struct FSideScrollerInput
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Input")
	uint32 bFire : 1;

	void Fire(bool bPressed);
};


UCLASS(config=Game)
class ASideScrollerCharacter : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

	// Side view camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	// Camera boom positioning the camera beside the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Collects and counts the coins of the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCoinCollector* CoinCollector;

	// Collects and counts the coins of the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UHealthCollector* HealthCollector;

	// Collects weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UWeaponCollector* WeaponCollector;

protected:

	// Called for side to side input
	void MoveRight(float Val);

	// Called to spawn projectiles
	void Fire();

	// Called to stop spawning projectiles
	void StopFire();

	// Handle touch inputs.
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	// Handle touch stop event.
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	// Side scroller input structure.
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	FSideScrollerInput SideScrollerInput;

public:
	ASideScrollerCharacter();

	virtual void BeginPlay();

	//~ Begin IDamageInterface
	virtual void ReceiveDamage(int32 IncomingDamage) override;
	virtual int32 GetHealthRemaining() override;
	//~ End IDamageInterface

	const FSideScrollerInput& GetCurrentInput() { return SideScrollerInput; }

	// Destroys the enemy and can used for special effects
	UFUNCTION(BlueprintNativeEvent, Category = "SideScrollerCharacter")
	void OnDeath();
	virtual void OnDeath_Implementation();


	void ReceiveOnGameWon();

	void AddHealth(int32 Amount);

	// Current health value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter", meta = (ClampMin = "0.0"))
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter", meta = (ClampMin = "0.0"))
	int32 MaxHealth;
};
