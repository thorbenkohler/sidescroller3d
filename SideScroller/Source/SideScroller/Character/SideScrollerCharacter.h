// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemInterface.h"

#include "GameFramework/Character.h"

#include "Interfaces/DamageInterface.h"
#include "Interfaces/HealthInterface.h"

#include "SideScrollerCharacter.generated.h"

UCLASS(config = Game)
class ASideScrollerCharacter : public ACharacter,
                               public IAbilitySystemInterface,
                               public IHealthInterface
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

    // Sets the AimDirection
    void AimHorizontal(float Value);
    void AimVertical(float Value);

    // Opens the ingame menu
    void OpenIngameMenu();

    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    // End of APawn interface

public:
    ASideScrollerCharacter();

    virtual void BeginPlay();

    // Can be used for effects
    UFUNCTION(BlueprintNativeEvent, Category = "SideScrollerCharacter")
    void OnDeath() const override;
    virtual void OnDeath_Implementation();

    // Handles player-enemy collision
    UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerCharacter")
    void EnemyCollidedWithPlayer();

	// Called when the actor falls out of the world 'safely' (below KillZ and such)
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

    UAbilitySystemComponent* GetAbilitySystemComponent() const override
    {
        return Cast<UAbilitySystemComponent>(AbilitySystem);
    };

    UHealthComponent* GetHealthComponent() const override
    {
        return HealthComponent;
    };

	// Sets the character to its last checkpoint
	void ReceiveOnRestartAtLastCheckpoint();

	// Used to reset the character and or play effects
	UFUNCTION(BlueprintNativeEvent, Category = "SideScrollerCharacter")
	void OnRevive();
	virtual void OnRevive_Implementation();

    // Notifies via Delegates every observer about the character's landing
    UFUNCTION(BlueprintCallable, Category = "SideScrollerCharacter")
    void NotifyResetCombo(const FHitResult& Hit);

    void Landed(const FHitResult& Hit);

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

    // Ability System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    class USideScrollerAbilitySystemComponent* AbilitySystem;

	// Data which manages the Health of the Player
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SideScrollerCharacter")
    const UHealthAttributeSet* HealthAttributeSet;

	// Data which gives the weapon it's damage
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SideScrollerCharacter")
	const UDamageAttributeSet* DamageAttributeSet;

	// To jump and hang off of walls
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UWallJump* WallJump;

	// Used to reset to the default gravity scale when it was changed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	float DefaultGravityScale;

	// Used to respawn the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	FTransform RespawnPosition;

    // Used to prevent character from walking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    bool bBlockMovement;

    // Used for the Shotdirection
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    FVector AimDirection;
};
