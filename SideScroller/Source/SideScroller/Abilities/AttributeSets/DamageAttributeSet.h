// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerAttributeSet.h"
#include "DamageAttributeSet.generated.h"


UCLASS(BlueprintType)
class UDamageAttributeSet : public USideScrollerAttributeSet
{
	GENERATED_BODY()

public:
	static const float MAX_DAMAGE;

	static const FGameplayAttribute& DamageAttribute();

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PostInitializeProperties(bool bInitialInit) override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Damage")
	float Damage;
};
