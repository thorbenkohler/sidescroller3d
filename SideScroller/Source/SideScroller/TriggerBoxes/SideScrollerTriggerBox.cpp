// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerTriggerBox.h"
#include "Runtime/Engine/Public/WorldCollision.h"

// Called when the game starts or when spawned
void ASideScrollerTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    UShapeComponent* ShapeComponent = GetCollisionComponent();

    if (!IsValid(ShapeComponent))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Not valid ShapeComponent."));
        return;
    }

    ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &ASideScrollerTriggerBox::OnOverlapBegin);
}

void ASideScrollerTriggerBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                             const FHitResult& SweepResult)
{
    UE_LOG(SideScrollerLog, Log, TEXT("SideScrollerTriggerBox %s collided with %s"), *GetName(),
           *(OtherActor->GetName()));
}
