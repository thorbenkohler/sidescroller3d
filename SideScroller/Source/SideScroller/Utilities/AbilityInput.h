// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilityInput.generated.h"

// Example for an enum the FGameplayAbiliyInputBinds may use to map input to ability slots.
UENUM(BlueprintType)
enum class EAbilityInput : uint8
{
	QSkill UMETA(DisplayName = "QSkill"),
	ESKill UMETA(DisplayName = "ESkill"),
	RSkill UMETA(DisplayName = "RSkill"),
	FireWeapon UMETA(DisplayName = "Fire Weapon"),
};
