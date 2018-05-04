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
	InvalidScopedModifierAttributes.Add(GetAttributes().HealthDef);

	RelevantAttributesToCapture.Add(GetAttributes().DamageDef);
}

void UDamageEffectExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Health = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAttributes().HealthDef, EvaluationParameters, Health);

	float Damage = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAttributes().DamageDef, EvaluationParameters, Damage);

	float DamageDone = FMath::Min<float>(Damage, Health);

	UE_LOG(SideScrollerLog, Log, TEXT("%s Damage done %f"), *LOG_STACK, DamageDone);

	if (DamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(GetAttributes().HealthProperty, EGameplayModOp::Additive, -DamageDone));
	}
}
