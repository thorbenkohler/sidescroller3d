// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHighscore.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLER_API UPlayerHighscore : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHighscore();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Gets called when the player dies
	virtual void ReceiveOnPlayerDied();

	// Get called when the game was finished succesful
	virtual void ReceiveOnGameWon();
	
	// Stores the amount of health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerHighscore")
	class UHealthCollector* HealthCollector;

	// Stores the amount of coins
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerHighscore")
	class UCoinCollector* CoinCollector;
};
