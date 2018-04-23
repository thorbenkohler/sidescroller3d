// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Abilities/AttributeSets/HealthAttributeSet.h"
#include "GameplayEffectExtension.h"

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    USideScrollerDelegates::OnPlayerChangeHealth.AddUObject(this, &UHealthComponent::ReceiveOnPlayerChangeHealth);
    USideScrollerDelegates::OnPlayerAddHealth.AddUObject(this, &UHealthComponent::ReceiveOnPlayerAddHealth);
	USideScrollerDelegates::OnHudShown.AddUObject(this, &UHealthComponent::ReceiveOnHudShown);

	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("HealthComponent has no valid owner."));
		return;
	}

	UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);

	if (!IsValid(AbilitySystem))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("%s AbilitySystem is not valid."), *LOG_STACK);
		return;
	}

    FOnGameplayAttributeValueChange& ValueChangedDelegate =
        AbilitySystem->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::HealthAttribute());
    ValueChangedDelegate.AddUObject(this, &UHealthComponent::ReceiveOnHealthAttributeChanged);
}

void UHealthComponent::ReceiveOnHealthAttributeChanged(const FOnAttributeChangeData& Callback)
{
	UE_LOG(SideScrollerLog, Log, TEXT("%s"), *LOG_STACK);
	if (Callback.GEModData == nullptr)
	{
		return;
	}

	if (FMath::IsNearlyEqual(Callback.OldValue, Callback.NewValue))
	{
		return;
	}

	AActor* DamageCauser = Callback.GEModData->EffectSpec.GetEffectContext().GetOriginalInstigator();
	MulticastSetHealth(Callback.OldValue, Callback.NewValue, DamageCauser);
	//Health = (uint32) Callback.NewValue;
}

void UHealthComponent::MulticastSetHealth_Implementation(float OldHealth, float NewHealth, AActor* DamageCauser)
{
	//if (GetWorld() && OldHealth > NewHealth)
	//{
	//	LastTimeDamageTaken = GetWorld()->GetRealTimeSeconds();
	//}

	//// Notify listeners.
	//OnHealthChanged.Broadcast(OldHealth, NewHealth, DamageCauser);

	//// Notify player owner.
	//ARTSPlayerController* PlayerOwner = Cast<ARTSPlayerController>(GetOwner()->GetOwner());

	//if (IsValid(PlayerOwner))
	//{
	//	PlayerOwner->NotifyOnActorHealthChanged(GetOwner(), OldHealth, NewHealth, DamageCauser);
	//}
}


void UHealthComponent::ReceiveOnPlayerChangeHealth(int32 Amount)
{
    Health = Amount;
}

void UHealthComponent::ReceiveOnPlayerAddHealth(int32 Amount)
{
    if (Health >= MaxHealth)
    {
        return;
    }

    if ((Amount + Health) >= MaxHealth)
    {
        Health = MaxHealth;
    }
    else
    {
        Health += Amount;
    }

    USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(Health);
}

void UHealthComponent::DamageTaken(int32 Amount)
{
    UE_LOG(SideScrollerLog, Log, TEXT("Incoming player damage %d"), Amount);
    if (Amount >= Health)
    {
        if (Health >= 0)
        {
            AActor* Owner = GetOwner();
            ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

            if (!IsValid(SideScrollerCharacter))
            {
                UE_LOG(SideScrollerLog, Error, TEXT("Cast to SideScroller from Owner was invalid."));
                return;
            }

            USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(0);
            SideScrollerCharacter->OnDeath();
        }
        return;
    }
    Health -= Amount;
    USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(Health);
}

void UHealthComponent::ReceiveOnHudShown()
{
	if (Health <= 0)
	{
		USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(MaxHealth);
		return;
	}
	USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(Health);
}
