// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "SideScrollerAbilitySystemComponent.generated.h"

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

	// Sets the level of this actor. This might change the attributes of the actor.
	UFUNCTION(BlueprintCallable, Category = "SideScroller")
	void SetLevel(int32 NewLevel);

	// Gets the current level of this actor.
	int32 GetLevel() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SideScroller")
	FGameplayTag NameTag;

	// Current level of the actor.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SideScroller")
	int32 Level = 1;
};
