// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "SideScrollerGameMode.h"
#include "Collectable.generated.h"


UCLASS()
class SIDESCROLLER_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the actual form for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	// Sets the actual form for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectable", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	// Gets triggered, when the actor collides with another actor
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Describes with what the collectable collides
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
	FName CollisionProfile;

	// Reference to the blueprint of the collectable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
	TSoftObjectPtr<UBlueprint> ReferencedCollectable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
