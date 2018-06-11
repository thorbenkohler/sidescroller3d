// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterDirection.generated.h"

// Example for an enum the FGameplayAbiliyInputBinds may use to map input to ability slots.
UENUM(BlueprintType)
enum class ECharacterDirection : uint8
{
	None UMETA(DisplayName = "None"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	LeftToRight UMETA(DisplayName = "LeftToRight"),
	RightToLeft UMETA(DisplayName = "RightToLeft"),
};
