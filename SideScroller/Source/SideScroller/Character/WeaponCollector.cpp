// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponCollector.h"
#include "SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UWeaponCollector::UWeaponCollector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWeaponCollector::BeginPlay()
{
	Super::BeginPlay();

	USideScrollerDelegates::OnCollectableWeaponAdded.AddUObject(this, &UWeaponCollector::ReceiveOnCollectableWeaponAdded);
}


// Called every frame
void UWeaponCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UWeaponCollector::ReceiveOnCollectableWeaponAdded(AWeapon* Weapon)
{
	FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, false);
	AActor* Owner = GetOwner();
	Weapon->AttachToActor(Owner, Rules);
	Weapon->SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);
	Weapon->SetActorRelativeLocation(Weapon->Offset);
	UE_LOG(LogTemp, Log, TEXT("Collectable Weapon %s added to %s"), *(Weapon->GetName()), *GetName());
}
