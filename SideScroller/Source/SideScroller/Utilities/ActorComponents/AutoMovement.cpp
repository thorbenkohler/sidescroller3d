// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoMovement.h"

void UAutoMovement::Move(UStaticMeshComponent* StaticMeshComponent)
{
	OnMove(StaticMeshComponent);
}

void UAutoMovement::MoveFinished()
{
	OnMoveFinished();
}
