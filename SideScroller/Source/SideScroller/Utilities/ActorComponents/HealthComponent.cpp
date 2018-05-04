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

    USideScrollerDelegates::OnPlayerAddHealth.AddUObject(this, &UHealthComponent::ReceiveOnPlayerAddHealth);
    USideScrollerDelegates::OnHudShown.AddUObject(this, &UHealthComponent::ReceiveOnHudShown);

    AActor* Owner = GetOwner();

    if (!IsValid(Owner))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("HealthComponent has no valid owner."));
        return;
    }

    AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);

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
    float Health = Callback.NewValue;

    AActor* Owner = GetOwner();
    IHealthInterface* HealthInterface = Cast<IHealthInterface>(Owner);

    if (!HealthInterface)
    {
        UE_LOG(SideScrollerLog, Error, TEXT("%s Owner %s is not of type UHealthInterface."), *LOG_STACK,
               *Owner->GetName());
        return;
    }

    if (Health <= 0)
    {
        HealthInterface->OnDeath();
    }

    ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

    if (!IsValid(SideScrollerCharacter))
    {
        return;
    }

    // Updating Player HUB
    if (!IsValid(AbilitySystem))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("%s AbilitySystem is not valid."), *LOG_STACK);
        return;
    }

    USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(Health);
}

void UHealthComponent::MulticastSetHealth_Implementation(float OldHealth, float NewHealth, AActor* DamageCauser)
{
    // if (GetWorld() && OldHealth > NewHealth)
    //{
    //	LastTimeDamageTaken = GetWorld()->GetRealTimeSeconds();
    //}

    //// Notify listeners.
    // OnHealthChanged.Broadcast(OldHealth, NewHealth, DamageCauser);

    //// Notify player owner.
    // ARTSPlayerController* PlayerOwner = Cast<ARTSPlayerController>(GetOwner()->GetOwner());

    // if (IsValid(PlayerOwner))
    //{
    //	PlayerOwner->NotifyOnActorHealthChanged(GetOwner(), OldHealth, NewHealth, DamageCauser);
    //}
}

// TODO change into ability, that a gameplay effectexeccalc does the calculation
void UHealthComponent::ReceiveOnPlayerAddHealth(int32 Amount)
{
    float MaxHealth = AbilitySystem->GetNumericAttribute(UHealthAttributeSet::MaxHealthAttribute());
    float Health = AbilitySystem->GetNumericAttribute(UHealthAttributeSet::HealthAttribute());

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

void UHealthComponent::ReceiveOnHudShown()
{
    float MaxHealth = AbilitySystem->GetNumericAttribute(UHealthAttributeSet::MaxHealthAttribute());
    float Health = AbilitySystem->GetNumericAttribute(UHealthAttributeSet::HealthAttribute());

    if (Health <= 0)
    {
        USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(MaxHealth);
        return;
    }
    USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(Health);
}
