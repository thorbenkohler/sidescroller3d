// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    USideScrollerDelegates::OnPlayerChangeHealth.AddUObject(this, &UHealthComponent::ReceiveOnPlayerChangeHealth);
    USideScrollerDelegates::OnPlayerAddHealth.AddUObject(this, &UHealthComponent::ReceiveOnPlayerAddHealth);
    USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(MaxHealth);
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
