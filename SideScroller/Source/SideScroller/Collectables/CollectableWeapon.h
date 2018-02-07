// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "SideScrollerGameMode.h"
#include "Collectable.h"
#include "CollectableWeapon.generated.h"


UCLASS()
class SIDESCROLLER_API ACollectableWeapon : public ACollectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the actual form for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	// Sets the actual form for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	// Gets triggered, when the actor collides with another actor
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
