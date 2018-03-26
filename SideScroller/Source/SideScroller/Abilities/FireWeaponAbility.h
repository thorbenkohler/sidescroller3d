// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/SideScrollerGameplayAbility.h"
#include "FireWeaponAbility.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API UFireWeaponAbility : public USideScrollerGameplayAbility
{
	GENERATED_BODY()

public:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
								 const FGameplayAbilityActorInfo* ActorInfo, 
		                         const FGameplayAbilityActivationInfo ActivationInfo, 
								 const FGameplayEventData* TriggerEventData) override;
	//~ End UGameplayAbility Interface

	UFUNCTION(BlueprintImplementableEvent, Category = "FireWeaponAbility")
	void OnActivated();
};
