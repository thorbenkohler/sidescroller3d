// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/AttributeSets/SideScrollerAttributeSet.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"

ASideScrollerCharacter::ASideScrollerCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Create a camera boom attached to the root (capsule)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->TargetArmLength = 500.f;
    CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
    CameraBoom->RelativeRotation = FRotator(0.f, 180.f, 0.f);

    // Create a camera and attach to boom
    SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;            // Face in the direction we are moving..
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->GravityScale = 4.f;
    GetCharacterMovement()->AirControl = 0.80f;
    GetCharacterMovement()->JumpZVelocity = 1000.f;
    GetCharacterMovement()->GroundFriction = 3.f;
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
    GetCharacterMovement()->MaxFlySpeed = 300.f;

    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

    CreateDefaultSubobject<UHealthCollector>(TEXT("HealthCollector"));
    CreateDefaultSubobject<UCoinCollector>(TEXT("CoinCollector"));
    CreateDefaultSubobject<UPlayerEnemyCollision>(TEXT("PlayerEnemyCollision"));
    CreateDefaultSubobject<UPlayerHighscore>(TEXT("PlayerHighscore"));

    WeaponCollector = CreateDefaultSubobject<UWeaponCollector>(TEXT("WeaponCollector"));
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    AbilitySystem = CreateDefaultSubobject<USideScrollerAbilitySystemComponent>(TEXT("AbilitySystem"));
    SideScrollerAttributeSet = CreateDefaultSubobject<USideScrollerAttributeSet>(TEXT("AttributeSet"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASideScrollerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // set up gameplay key bindings
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("OpenMenu", IE_Pressed, this, &ASideScrollerCharacter::OpenIngameMenu);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASideScrollerCharacter::MoveRight);

    AbilitySystem->BindAbilityActivationToInputComponent(
        PlayerInputComponent, FGameplayAbiliyInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
}

void ASideScrollerCharacter::OpenIngameMenu()
{
    USideScrollerDelegates::OnOpenIngameMenu.Broadcast();
}

void ASideScrollerCharacter::MoveRight(float Value)
{
    // add movement in that direction
    AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}

void ASideScrollerCharacter::BeginPlay()
{
    Super::BeginPlay();

    USideScrollerDelegates::OnGameWon.AddUObject(this, &ASideScrollerCharacter::ReceiveOnGameWon);

    if (!IsValid(AbilitySystem))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("AbilitySystem was not valid."));
        return;
    }

    if (!IsValid(UseAbility))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("The Ability is not valid."));
        return;
    }

    if (HasAuthority())
    {
        AbilitySystem->GiveAbility(
            FGameplayAbilitySpec(UseAbility.GetDefaultObject(), 1, (uint32)AbilityInput::UseAbility1));
    }
    AbilitySystem->InitAbilityActorInfo(this, this);

    if (!IsValid(SideScrollerAttributeSet))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("SideScrollerAttributeSet was not valid."));
        return;
    }

    if (!IsValid(AttributeDataTable))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("No valid AttributeDataTable was set."));
        return;
    }

    const UAttributeSet* AttributeSet =
        AbilitySystem->InitStats(USideScrollerAttributeSet::StaticClass(), AttributeDataTable);
    SideScrollerAttributeSet = Cast<USideScrollerAttributeSet>(AttributeSet);

    if (!IsValid(SideScrollerAttributeSet))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("Cast failed. AttributeSet is not of type USideScrollerAttributeSet"))
        return;
    }

    UE_LOG(SideScrollerLog, Log, TEXT("%f max: %f"), SideScrollerAttributeSet->Health.GetCurrentValue(),
           SideScrollerAttributeSet->MaxHealth.GetCurrentValue());
}

void ASideScrollerCharacter::DamageTaken(int32 IncomingDamage)
{
    if (!IsValid(HealthComponent))
    {
        UE_LOG(SideScrollerLog, Error, TEXT("No valid HealthComponent found."));
        return;
    }
    HealthComponent->DamageTaken(IncomingDamage);
}

void ASideScrollerCharacter::ReceiveOnGameWon()
{
    DisableInput((APlayerController*)GetController());
    SetActorEnableCollision(false);
}

void ASideScrollerCharacter::OnDeath_Implementation()
{
    DisableInput((APlayerController*)GetController());
    SetActorEnableCollision(false);
    USideScrollerDelegates::OnPlayerDied.Broadcast();
}
