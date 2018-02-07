// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageInterface.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class SIDESCROLLER_API AEnemy : public APawn, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//~ Begin IDamageInterface
	virtual void ReceiveDamage(int32 IncomingDamage) override;
	virtual int32 GetHealthRemaining() override;
	//~ End IDamageInterface

	// Destroys the enemy and can used for special effects
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void Die();

	// Sets the actual form for the enemy
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;
	 
	// Current health value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float Health;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
