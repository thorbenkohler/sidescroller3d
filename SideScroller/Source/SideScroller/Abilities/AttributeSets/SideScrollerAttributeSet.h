// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "SideScrollerAttributeSet.generated.h"


UCLASS()
class USideScrollerAttributeSet : public UAttributeSet
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerCharacter Attributes | Health")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SideScrollerCharacter Attributes | MaxHealth")
	FGameplayAttributeData MaxHealth;
 
	// FGameplayAttributeData is the intended struct to be used for attributes by the system. However,
	// attributes can also be declared as simple floats. I am unsure if the attribute initialization method
	// further down functions with the struct, however the float method seems to be the more dated one.

	static FGameplayAttribute HealthAttribute();
	static FGameplayAttribute MaxHealthAttribute();

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};
