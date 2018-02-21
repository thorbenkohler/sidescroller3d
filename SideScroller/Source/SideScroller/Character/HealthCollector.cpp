// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthCollector.h"
#include "UI/HighScoreWidget.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UHealthCollector::UHealthCollector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthCollector::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

	if (!IsValid(SideScrollerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is no SideScrollerCharacter."));
		return;
	}

	USideScrollerDelegates::OnPlayerChangeHealth.AddUObject(this, &UHealthCollector::ReceiveOnPlayerChangeHealth);
	USideScrollerDelegates::OnCollectableHealthAdded.AddUObject(this, &UHealthCollector::ReceiveOnCollectableHealthAdded);
	USideScrollerDelegates::OnPlayerChangeHealth.Broadcast(MaxHealth);
}

// Called every frame
void UHealthCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthCollector::ReceiveOnCollectableHealthAdded(int32 Amount)
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

void UHealthCollector::ReceiveOnPlayerChangeHealth(int32 Amount)
{
	Health = Amount;
}

void UHealthCollector::DamageTaken(int32 Amount)
{
	UE_LOG(LogTemp, Log, TEXT("Incoming player damage %d"), Amount);
	if (Amount >= Health)
	{
		if (Health >= 0)
		{
			AActor* Owner = GetOwner();
			ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

			if (!IsValid(SideScrollerCharacter))
			{
				UE_LOG(LogTemp, Error, TEXT("Cast to SideScroller from Owner was invalid."));
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
