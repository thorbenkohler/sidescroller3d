// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/DamageInterface.h"
#include "GameFramework/Character.h"
#include "WeaponCollector.h"
#include "PlayerEnemyCollision.h"
#include "AbilitySystemInterface.h"
#include "Utilities/InputEnums.h"
#include "WallJump.h"
#include "SideScrollerCharacter.generated.h"

UCLASS(config = Game)
class ASideScrollerCharacter : public ACharacter, public IDamageInterface, public IAbilitySystemInterface
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

    // Opens the ingame menu
    void OpenIngameMenu();

    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    // End of APawn interface

public:
    ASideScrollerCharacter();

    virtual void BeginPlay();

    //~ Begin IDamageInterface
    virtual void DamageTaken(int32 IncomingDamage) override;
    //~ End IDamageInterface

    // Can be used for effects and disables input and collision
    UFUNCTION(BlueprintNativeEvent, Category = "SideScrollerCharacter")
    void OnDeath();
    virtual void OnDeath_Implementation();

    // Handles player-enemy collision
    UFUNCTION(BlueprintImplementableEvent, Category = "SideScrollerCharacter")
    void EnemyCollidedWithPlayer();

    // Handles the player input and collision
    void ReceiveOnGameWon();

    UAbilitySystemComponent* GetAbilitySystemComponent() const override
    {
        return Cast<UAbilitySystemComponent>(AbilitySystem);
    };

    // Collects and counts the coins of the player
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    class UCoinCollector* CoinCollector;

    // Collects and counts the health of the player
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    class UHealthCollector* HealthCollector;

    // Collects weapons
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    UWeaponCollector* WeaponCollector;

    // Handles player collision with enemies
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    UPlayerEnemyCollision* PlayerEnemyCollision;

    // Manages data that is needed at the highscore
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    class UPlayerHighscore* PlayerHighscore;

    // Manages damage and adding health
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    class UHealthComponent* HealthComponent;

    // Ability System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
    USideScrollerAbilitySystemComponent* AbilitySystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SideScrollerCharacter")
    const UHealthAttributeSet* HealthAttributeSet;

	// To jump and hang off of walls
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	UWallJump* WallJump;

	// Used to reset to the default gravity scale when it was changed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	float DefaultGravityScale;
};
