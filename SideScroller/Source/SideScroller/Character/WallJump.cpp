// Fill out your copyright notice in the Description page of Project Settings.

#include "WallJump.h"
#include "Components/BoxComponent.h"


UWallJump::UWallJump()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.bStartWithTickEnabled = false;
}

// Called when the game starts
void UWallJump::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
	BindDelegates();

	Character = Cast<ACharacter>(Owner);

	if (!IsValid(Character))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Owner is not of type ACharacter in WallJump."));
		return;
	}

    SideScrollerCharacter = Cast<ASideScrollerCharacter>(Owner);

    if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Owner is not of type ASideScrollerCharacter in WallJump."));
		return;
    }

    SkeletalMeshComponent = Owner->FindComponentByClass<USkeletalMeshComponent>();

    if (!IsValid(SkeletalMeshComponent))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("No SkeletalMeshComponent found in Owner in WallJump."));
        return;
    }

    CharacterMovementComponent = Owner->FindComponentByClass<UCharacterMovementComponent>();

    if (!IsValid(CharacterMovementComponent ))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("No CharacterMovementComponent found in Owner in WallJump."));
        return;
    }

	SideScrollerCharacter->DefaultGravityScale = CharacterMovementComponent->GravityScale;
}

void UWallJump::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentInputVector = Character->GetLastMovementInputVector();

	// If the input changes to the opposite direction or is 0 the character loses the grip
    if (LastControlInputVector.Y > 0 && CurrentInputVector.Y < 0 ||
        LastControlInputVector.Y < 0 && CurrentInputVector.Y > 0 || CurrentInputVector.Y == 0)
    {
        CurrentInputVector.Y == 0 ? SetWallSlidingState() : ResetWallState();
    }

	// if the character hits the bottom (e.g. after sliding down)
    if (!CharacterMovementComponent->IsFalling())
	{
		ResetWallState();
	}

	LastControlInputVector = CurrentInputVector;

	// Character jumped (was set to -1 when overlapping)
	if (Character->JumpCurrentCount >= 0)
	{
		ResetWallState();
		return;
	}
}

void UWallJump::Activate(bool bReset)
{
	Super::Activate(bReset);

	BindDelegates();
}

void UWallJump::Deactivate()
{
	Super::Deactivate();

	GetOwner()->OnActorBeginOverlap.RemoveAll(this);
}

void UWallJump::BindDelegates()
{
    AActor* Owner = GetOwner();
    Owner->OnActorBeginOverlap.AddDynamic(this, &UWallJump::ActorBeginOverlap);
    Owner->OnActorEndOverlap.AddDynamic(this, &UWallJump::ActorEndOverlap);
}

void UWallJump::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    UBoxComponent* BoxComponent = OtherActor->FindComponentByClass<UBoxComponent>();

    if (!IsValid(BoxComponent))
    {
        return;
    }

    if (!BoxComponent->GetCollisionProfileName().IsEqual(WallJumpCollisionProfile))
    {
        return;
    }

	SetWallState();
}

void UWallJump::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ResetWallState();
}

void UWallJump::SetWallState()
{
	LastControlInputVector = FVector::ZeroVector;
	Character->GetActorRotation().Yaw < 0 ? LastControlInputVector.Y = -1.f : LastControlInputVector.Y = 1.f;

	if (!IsValid(CharacterMovementComponent))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("CharacterMovementComponent is not valid in WallJump."));
		return;
	}

	// Lets the character float when jumping against a wall
	CharacterMovementComponent->GravityScale = 0.0f;
	CharacterMovementComponent->Velocity.Z = 0.0f;

	SetComponentTickEnabled(true);

	bHangsOnWall = true;

	if (!IsValid(Character))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("Character is not valid in WallJump."));
		return;
	}

	Character->ResetJumpState();
	Character->JumpCurrentCount = -1;

	if (!IsValid(SkeletalMeshComponent))
	{
		UE_LOG(SideScrollerLog, Error, TEXT("SkeletalMeshComponent is invalid in WallJump."));
		return;
	}

	SkeletalMeshComponent->SetWorldScale3D(FVector::OneVector);

	if (Character->GetActorRotation().Yaw < 0)
	{
		SkeletalMeshComponent->SetWorldScale3D(FVector(-1.f, 1.f, 1.f));
	}
}

void UWallJump::SetWallSlidingState()
{
	if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("SideScrollerCharacter is not valid in WallJump."));
        return;
    }

    if (!IsValid(CharacterMovementComponent))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("CharacterMovementComponent is not valid in WallJump."));
        return;
    }

	CharacterMovementComponent->GravityScale = SideScrollerCharacter->DefaultGravityScale * SlideGravityModifier;
	bIsSliding = true;
}

void UWallJump::ResetWallState()
{
	SetComponentTickEnabled(false);

	bHangsOnWall = false;
	bIsSliding = false;

	if (!IsValid(SideScrollerCharacter))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("SideScrollerCharacter is not valid in WallJump."));
        return;
    }

    if (!IsValid(CharacterMovementComponent))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("CharacterMovementComponent is not valid in WallJump."));
        return;
    }

	CharacterMovementComponent->GravityScale = SideScrollerCharacter->DefaultGravityScale;

	USkeletalMeshComponent* SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SkeletalMeshComponent->SetWorldScale3D(FVector::OneVector);
}
