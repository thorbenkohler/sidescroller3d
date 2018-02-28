// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollectableHealth.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIDESCROLLER_API UCollectableHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollectableHealth();

	// Gets triggered, when the actor collides with another actor
	UFUNCTION() 
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	// Gets added to the Players score
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CollectableHealth", meta = (AllowPrivateAccess = "true"))
	int32 Amount;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
