// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectable.h"
#include "Utilities/SideScrollerStatics.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Runtime/Engine/Public/WorldCollision.h"


// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();

	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetRootComponent());
	
	if (!IsValid(PrimitiveComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("No primitive component found in %s"), *GetName());
		return;
	}

	PrimitiveComponent->SetCollisionProfileName(FName(TEXT("Collectable:General")));
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Collectable %s collided with %s"), *GetName(), *(OtherActor->GetName()));
	USideScrollerDelegates::OnCollectableAdded.Broadcast(this);
}
