// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "GameFramework/Actor.h"
#include "Health.generated.h"

class ASideScrollerCharacter;

UCLASS()
class SIDESCROLLER_API AHealth : public APowerUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealth();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
