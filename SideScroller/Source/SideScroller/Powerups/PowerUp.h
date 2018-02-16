// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

class ASideScrollerCharacter;

UCLASS()
class SIDESCROLLER_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the actual form for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PowerUp", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
