// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "EnemyImpact.generated.h"


UCLASS()
class SIDESCROLLER_API UEnemyImpact : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintImplementableEvent, Category = "EnemyImpact")
	void Impact();
};
