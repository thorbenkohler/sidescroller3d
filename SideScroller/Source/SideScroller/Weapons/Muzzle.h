// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Muzzle.generated.h"


UCLASS(Blueprintable)
class SIDESCROLLER_API UMuzzle : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMuzzle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
