// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/DamageInterface.h"
#include "GameFramework/Character.h"
#include "WeaponCollector.h"
#include "AbilitySystemInterface.h"
#include "SideScrollerCharacter.generated.h"


//Example for an enum the FGameplayAbiliyInputBinds may use to map input to ability slots.
UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	UseAbility1 UMETA(DisplayName = "Use Spell 1"),
	UseAbility2 UMETA(DisplayName = "Use Spell 2"),
	UseAbility3 UMETA(DisplayName = "Use Spell 3"),
	UseAbility4 UMETA(DisplayName = "Use Spell 4"),
	FireWeapon UMETA(DisplayName = "Fire Weapon"),
};


UCLASS(config=Game)
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

	// Called to spawn projectiles
	void Fire();

	// Called to stop spawning projectiles
	void StopFire();

	// Opens the ingame menu
	void OpenIngameMenu();

	// Handle touch inputs.
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	// Handle touch stop event.
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

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

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };

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
	class UPlayerEnemyCollision* PlayerEnemyCollision;

	// Manages data that is needed at the highscore
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UPlayerHighscore* PlayerHighscore;

	// Manages damage and adding health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScrollerCharacter")
	class UHealthComponent* HealthComponent;

	// Ability System
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	// One single ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TSubclassOf<class UGameplayAbility> UseAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	UDataTable* AttributeDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	const USideScrollerAttributeSet* SideScrollerAttributeSet;
};
