// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableCoin.h"
#include "Powerups/Coin.h"
#include "Utilities/SideScrollerStatics.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Runtime/Engine/Public/WorldCollision.h"


// Sets default values
ACollectableCoin::ACollectableCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(CapsuleComponent);
}

// Called when the game starts or when spawned
void ACollectableCoin::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectableCoin::OnOverlapBegin);
}

// Called every frame
void ACollectableCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectableCoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	USideScrollerDelegates::OnCollectableCoinAdded.Broadcast(Amount);
	Destroy();
}
