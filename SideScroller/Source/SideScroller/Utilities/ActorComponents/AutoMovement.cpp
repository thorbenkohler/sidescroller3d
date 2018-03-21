// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoMovement.h"
#include "Utilities/SideScrollerDelegates.h"


// Sets default values for this component's properties
UAutoMovement::UAutoMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAutoMovement::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UAutoMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAutoMovement::Move(float TimeEllapsed, UStaticMeshComponent* StaticMeshComponent)
{
	OnMove(TimeEllapsed, StaticMeshComponent);
}

void UAutoMovement::MoveFinished()
{
	OnMoveFinished();
}
