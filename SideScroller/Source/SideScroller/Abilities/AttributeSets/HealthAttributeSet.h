// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerAttributeSet.h"
#include "HealthAttributeSet.generated.h"


UCLASS(BlueprintType)
class UHealthAttributeSet : public USideScrollerAttributeSet
{
	GENERATED_BODY()

public:
	static const float MAX_HEALTH;

	static const FGameplayAttribute& MaxHealthAttribute();
	static const FGameplayAttribute& HealthAttribute();

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PostInitializeProperties(bool bInitialInit) override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|MaxHealth")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
	float Health;
};
