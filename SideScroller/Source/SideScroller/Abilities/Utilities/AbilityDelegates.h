// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilityDelegates.generated.h"

UCLASS()
class SIDESCROLLER_API UAbilityDelegates : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDashOverlapBegin, AActor*);
	static FOnDashOverlapBegin OnDashOverlapBegin;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerEnemyCollision, class AEnemy*);
	static FOnPlayerEnemyCollision OnPlayerEnemyCollision;
};
