// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerTriggerBox.h"
#include "Checkpoint.generated.h"

UCLASS()
class SIDESCROLLER_API ACheckpoint : public ASideScrollerTriggerBox
{
	GENERATED_BODY()
	
public:

	// Used to set the last respawn position of the player
	UFUNCTION(BlueprintNativeEvent, Category = "SideScroller")
	void ReceiveActorBeginOverlap(AActor* OtherActor);
	virtual void ReceiveActorBeginOverlap_Implementation(AActor* OtherActor);
};
