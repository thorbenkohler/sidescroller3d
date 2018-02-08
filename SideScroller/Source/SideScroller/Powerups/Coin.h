// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/Muzzle.h"
#include "Coin.generated.h"

class ASideScrollerCharacter;

UCLASS()
class SIDESCROLLER_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the actual form for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
