// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectable.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Runtime/Engine/Public/WorldCollision.h"

void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(SideScrollerLog, Log, TEXT("Collectable %s collided with %s"), *GetName(), *(OtherActor->GetName()));
	USideScrollerDelegates::OnCollectableAdded.Broadcast(this);
}
