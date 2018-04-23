// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDESCROLLER_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Sets the health
    void ReceiveOnPlayerChangeHealth(int32 Amount);

    // Adds health
    void ReceiveOnPlayerAddHealth(int32 Amount);

	// When thehud was hidden and is shown again (for startup as well)
	void ReceiveOnHudShown();

    // Calculates if damage was taken and sets health
    void DamageTaken(int32 Amount);

	void ReceiveOnHealthAttributeChanged(const FOnAttributeChangeData& Callback);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetHealth(float OldHealth, float NewHealth, AActor* DamageCauser);

    // Current amount of Health
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent")
    int32 Health;

    // Maximum health of the player
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
    int32 MaxHealth;
};
