// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerAbilitySystemComponent.h"
#include "SideScroller.h"
#include "AbilitySystemGlobals.h"

#include "Character/SideScrollerCharacter.h"

#include "Interfaces/GameplayEffectInterface.h"

#include "Utilities/SideScrollerStatics.h"
#include "Utilities/AbilitySystemStatics.h"


void USideScrollerAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeAttributes(1, true);
}

FGameplayAbilitySpecHandle USideScrollerAbilitySystemComponent::GiveAbility(const FGameplayAbilitySpec& Spec)
{
    check(Spec.Ability);
    check(IsOwnerActorAuthoritative()); // Should be called on authority

    // If locked, add to pending list. The Spec.Handle is not regenerated when we receive, so returning this is ok.
    if (AbilityScopeLockCount > 0)
    {
        AbilityPendingAdds.Add(Spec);
        return Spec.Handle;
    }

    FGameplayAbilitySpec& OwnedSpec = ActivatableAbilities.Items[ActivatableAbilities.Items.Add(Spec)];

    if (OwnedSpec.Ability->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerActor)
    {
        // Create the instance at creation time
        CreateNewInstanceOfAbility(OwnedSpec, Spec.Ability);
    }

    OnGiveAbility(OwnedSpec);
    MarkAbilitySpecDirty(OwnedSpec);

    return OwnedSpec.Handle;
}

const UAttributeSet* USideScrollerAbilitySystemComponent::InitStats(TSubclassOf<class UAttributeSet> Attributes, const UDataTable* DataTable)
{
	const UAttributeSet* AttributeObj = NULL;
	if (Attributes)
	{
		AttributeObj = GetOrCreateAttributeSubobject(Attributes);
		if (AttributeObj && DataTable)
		{
			// This const_cast is OK - this is one of the few places we want to directly modify our AttributeSet properties rather
			// than go through a gameplay effect
			const_cast<UAttributeSet*>(AttributeObj)->InitFromMetaDataTable(DataTable);
		}
	}
	return AttributeObj;
}

void USideScrollerAbilitySystemComponent::InitializeAttributes(int AttributeLevel, bool bInitialInit)
{
	if (!NameTag.IsValid())
	{
		UE_LOG(SideScrollerLog, Warning, TEXT("%s invalid NameTag in %s"), *LOG_STACK, *GetOwner()->GetName())
		return;
	}

	FName GroupName = USideScrollerStatics::GetLastTagName(NameTag);

	// Note that this might cause a crash when no valid paths to data tables where specified in the 'Game.ini' file.
	UAbilitySystemGlobals* AbilitySystemGlobals = IGameplayAbilitiesModule::Get().GetAbilitySystemGlobals();

	if (!IsValid(AbilitySystemGlobals))
	{
		UE_LOG(SideScrollerLog, Log, TEXT("%s invalid."), *LOG_STACK);
		return;
	}

	FAttributeSetInitter* AttributeInitter = AbilitySystemGlobals->GetAttributeSetInitter();

	if (!AttributeInitter)
	{
		UE_LOG(SideScrollerLog, Warning, TEXT("%s invalid AttributeInitter in %s"), *LOG_STACK, *GetOwner()->GetName())
		return;
	}

	// This is a work around for a bug that happens at least in the editor. It might be that the 'SpawnedAttributes'
	// contains nullptr entries for some for some unknown reason. This has properly something to do with serialization.
	// 'AttributeInitter->InitAttributeSetDefaults' will crash when the array contains a nullptr.
	for (int32 i = SpawnedAttributes.Num() - 1; i >= 0; --i)
	{
		if (!IsValid(SpawnedAttributes[i]))
		{
			SpawnedAttributes.RemoveAt(i);
		}
	}

	AttributeInitter->InitAttributeSetDefaults(this, GroupName, AttributeLevel, bInitialInit);

	for (UAttributeSet* AttributeSet : SpawnedAttributes)
	{
		USideScrollerAttributeSet* SideScrollerAttributeSet = Cast<USideScrollerAttributeSet>(AttributeSet);

		if (!IsValid(SideScrollerAttributeSet))
		{
			continue;
		}

		SideScrollerAttributeSet->PostInitializeProperties(bInitialInit);

		UHealthAttributeSet* HealthAttributeSet = Cast<UHealthAttributeSet>(SideScrollerAttributeSet);

		if (!IsValid(HealthAttributeSet))
		{
			continue;
		}

		UE_LOG(SideScrollerLog, Log, TEXT("%s %f"), *LOG_STACK, HealthAttributeSet->MaxHealth);
	}
}


const UAttributeSet* USideScrollerAbilitySystemComponent::GetOrCreateAttributeSubobject(TSubclassOf<UAttributeSet> AttributeClass)
{
	AActor* OwningActor = GetOwner();
	const UAttributeSet* MyAttributes = nullptr;
	if (OwningActor && AttributeClass)
	{
		MyAttributes = GetAttributeSubobject(AttributeClass);
		if (MyAttributes)
		{
			UAttributeSet* Attributes = NewObject<UAttributeSet>(OwningActor, AttributeClass);
			SpawnedAttributes.AddUnique(Attributes);
			MyAttributes = Attributes;
			bIsNetDirty = true;
		}
	}

	return MyAttributes;
}

const UAttributeSet* USideScrollerAbilitySystemComponent::GetAttributeSubobject(const TSubclassOf<UAttributeSet> AttributeClass)
{
	for (const UAttributeSet* Set : SpawnedAttributes)
	{
		if (Set && Set->IsA(AttributeClass))
		{
			UE_LOG(SideScrollerLog, Log, TEXT("Set %s %s"), *Set->GetName(), *LOG_STACK);
			return Set;
		}
	}
	return NULL;
}

