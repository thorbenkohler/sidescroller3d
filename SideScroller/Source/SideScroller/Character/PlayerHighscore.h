// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerHighscore.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLER_API UPlayerHighscore : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Gets called when the player dies
	void ReceiveOnPlayerDied();

	// Get called when the game was finished succesful
	void ReceiveOnGameWon();
	
	// Stores the amount of health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerHighscore")
	class UHealthComponent* HealthComponent;

	// Stores the amount of coins
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerHighscore")
	class UCoinCollector* CoinCollector;
};
