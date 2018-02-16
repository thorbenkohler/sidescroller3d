// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WinGame.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLER_API UWinGame : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWinGame();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sends the according event
	UFUNCTION(BlueprintCallable, Category = "WinGame")
	void WinGame();
};
