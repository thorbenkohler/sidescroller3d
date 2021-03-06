// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Utilities/CharacterDirection.h"
#include "WallJump.generated.h"

UCLASS()
class SIDESCROLLER_API UWallJump : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWallJump();

	// Used to check the states, while hanging on the wall
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void Activate(bool bReset=false) override;
	virtual void Deactivate() override;

	// Registers the overlapping delegates
	void BindDelegates();

	// If the character overlaps with a wall he can hang on
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// If the character leaves the wall where he was hanging
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Sets everything that is needed to hang on the wall
	void SetWallState();

	// If the player chooses to slide down the wall
	void SetWallSlidingState();

	// Resets everything back to 'normal'
	void ResetWallState();

	// Used to check if the character/wall is able to hang on the wall
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallJump")
	FName WallJumpCollisionProfile;

	// Represents the hanging-on-wall state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WallJump")
	bool bHangsOnWall;

	// Represents the sliding state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WallJump")
	bool bIsSliding;

	// Used to modify the sliding speed on walls dependent on the gravity scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallJump")
	float SlideGravityModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallJump")
    FVector WallLaunchVelocity;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    // If the character lands on the ground, things need to be reset
    void ReceiveOnCharacterLanded(const FHitResult& Hit);

	// Cached instance from Owner
	class USkeletalMeshComponent* SkeletalMeshComponent;

	// Cached instance from Owner
	class ASideScrollerCharacter* SideScrollerCharacter;

	// Cached instance from Owner
	class UCharacterMovementComponent* CharacterMovementComponent;

	// Cached instance from Owner
	class ACharacter* Character;

	// GetPendingInputVector in APawn always gets Vector::Zero, so this is cached here instead
	FVector LastControlInputVector;

    // To reset the jump velocity
    float OldJumpZVelocity;

    bool bJumpedFromWall;
};
