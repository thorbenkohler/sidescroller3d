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
	virtual void DamageTaken(int32 IncomingDamage) override;
	//~ End IDamageInterface

	const FSideScrollerInput& GetCurrentInput() { return SideScrollerInput; }

	// Can be used for effects and disables input and collision
	UFUNCTION(BlueprintNativeEvent, Category = "SideScrollerCharacter")
	void OnDeath();
	virtual void OnDeath_Implementation();

	// Handles player-enemy collision
	UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerCharacter")
	void EnemyCollidedWithPlayer();

	// Handles the player input and collision
	void ReceiveOnGameWon();

	// Collects and counts the coins of the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UCoinCollector* CoinCollector;

	// Collects and counts the health of the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UHealthCollector* HealthCollector;

	// Collects weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UWeaponCollector* WeaponCollector;

	// Handles player collision with enemies
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UPlayerEnemyCollision* PlayerEnemyCollision;

	// Manages data that is needed at the highscore
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UPlayerHighscore* PlayerHighscore;

	// Manages damage and adding health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UHealthComponent* HealthComponent;

};
