// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SideScrollerTriggerBox.generated.h"


UCLASS()
class SIDESCROLLER_API ASideScrollerTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASideScrollerTriggerBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gets triggered, when the actor collides with another actor
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
