// Fill out your copyright notice in the Description page of Project Settings.

#include "FireWeaponAbility.h"
#include "SideScroller.h"


void UFireWeaponAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	UE_LOG(SideScrollerLog, Log, TEXT("FireWeaponAbility activated %s     %s    %s."), *Handle.ToString(), *ActorInfo->OwnerActor->GetName(), *ActivationInfo.GetActivationPredictionKey().ToString());

	OnActivated();
	//EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}