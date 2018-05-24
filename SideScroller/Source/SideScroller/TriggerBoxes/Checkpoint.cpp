// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"

void ACheckpoint::ReceiveActorBeginOverlap_Implementation(AActor* OtherActor)
{
	ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(OtherActor);

	if (!IsValid(SideScrollerCharacter))
	{
		return;
	}

	SideScrollerCharacter->RespawnPosition = GetTransform();
}
