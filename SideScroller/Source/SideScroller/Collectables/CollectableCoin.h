// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableCoin.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIDESCROLLER_API UCollectableCoin : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCollectableCoin();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Gets triggered, when the actor collides with another actor
	UFUNCTION() 
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	// Gets added to the Players score
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CollectableCoin", meta = (AllowPrivateAccess = "true"))
	int32 Amount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
