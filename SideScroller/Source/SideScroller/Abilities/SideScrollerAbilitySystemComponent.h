// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "SideScrollerAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API USideScrollerAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	FGameplayAbilitySpecHandle GiveAbility(const FGameplayAbilitySpec& AbilitySpec);

	virtual const UAttributeSet* InitStats(TSubclassOf<class UAttributeSet> Attributes, const UDataTable* DataTable);

	virtual const UAttributeSet* GetOrCreateAttributeSubobject(TSubclassOf<UAttributeSet> AttributeClass);

	virtual const UAttributeSet* GetAttributeSubobject(const TSubclassOf<UAttributeSet> AttributeClass);

	virtual void InitializeAttributes(int AttributeLevel, bool bInitialInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SideScroller")
	FGameplayTag NameTag;
};
