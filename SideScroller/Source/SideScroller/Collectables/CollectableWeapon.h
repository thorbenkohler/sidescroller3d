// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableWeapon.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIDESCROLLER_API UCollectableWeapon : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCollectableWeapon();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Gets triggered, when the actor collides with another actor
	UFUNCTION()
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	// Reference to the blueprint of the collectable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollectableWeapon")
	TSubclassOf<AActor> ReferencedCollectable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
