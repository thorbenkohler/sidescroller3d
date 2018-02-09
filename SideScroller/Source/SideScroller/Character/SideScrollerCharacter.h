// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SideScrollerCharacter.generated.h"

// TODO: Good or bad practice?
class ACollectable;
class AWeapon;
class ACoin;
class UCoinCollector;

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
class ASideScrollerCharacter : public ACharacter
{
	GENERATED_BODY()

	// Side view camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	// Camera boom positioning the camera beside the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// For general collecting purposes e.g. debug, achievements etc.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCollector* Collector;

	// Collects and counts the coins of the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCoinCollector* CoinCollector;

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

	// Returns SideViewCameraComponent subobject
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	// Returns CameraBoom subobject 
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Returns CoinCollector Actor Component
	FORCEINLINE class UCoinCollector* GetCoinCollector() const { return CoinCollector; }

	UFUNCTION(BlueprintCallable, Category = "SideScrollerCharacter")
	const FSideScrollerInput& GetCurrentInput() { return SideScrollerInput; }
};