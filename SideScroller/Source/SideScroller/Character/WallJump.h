// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WallJump.generated.h"

UCLASS()
class SIDESCROLLER_API UWallJump : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWallJump();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void SetWallState();
	void SetWallSlidingState();
	void ResetWallState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallJump")
	FName WallJumpCollisionProfile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WallJump")
	bool bHangsOnWall;

	// Used to modify the sliding speed on walls dependent on the gravity scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallJump")
	float SlideGravityModifier;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Cached instance from Owner
	class USkeletalMeshComponent* SkeletalMeshComponent;

	// Cached instance from Owner
	class ASideScrollerCharacter* SideScrollerCharacter;

	// Cached instance from Owner
	class UCharacterMovementComponent* CharacterMovementComponent;

	// Cached instance from Owner
	class ACharacter* Character;

	// GetPendingInputVector in pawn always get Vector::Zero, so this is cached here instead
	FVector LastControlInputVector;
};
