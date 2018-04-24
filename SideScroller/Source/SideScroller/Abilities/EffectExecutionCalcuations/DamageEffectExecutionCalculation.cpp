// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageEffectExecutionCalculation.h"
#include "Abilities/AttributeSets/HealthAttributeSet.h"
#include "Abilities/AttributeSets/DamageAttributeSet.h"
#include "AbilitySystemComponent.h"

struct AttStruct
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
										  
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage); 

	AttStruct()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHealthAttributeSet, Health, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UDamageAttributeSet, Damage, Source, false);
	}
};

// Note that we cannot just declare a static field because the constructor of the struct will run before
// important unreal types are initialized (like UTypeName::StaticClass()).
// Using this function wrapper around the static field will defer the assignment of the field to the point
// where the function runs the first time.
const AttStruct& GetAttributes()
{
	static AttStruct Attributes;
	return Attributes;
}

UDamageEffectExecutionCalculation::UDamageEffectExecutionCalculation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttStruct Attributes;

	RelevantAttributesToCapture.Add(GetAttributes().HealthDef);
	RelevantAttributesToCapture.Add(GetAttributes().DamageDef);
}
