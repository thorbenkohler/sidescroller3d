// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoMovement.h"

void UAutoMovement::Move(float TimeEllapsed, UStaticMeshComponent* StaticMeshComponent)
{
	OnMove(TimeEllapsed, StaticMeshComponent);
}

void UAutoMovement::MoveFinished()
{
	OnMoveFinished();
}
