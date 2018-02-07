// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventNames.generated.h"

UENUM(BlueprintType)
enum class EEventNames : uint8
{
	COLLECTABLE_ADDED UMETA(DisplayName = "COLLECTABLE_ADDED"),
};

UCLASS()
class SIDESCROLLER_API UEventNames : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString GetEventNameAsString(EEventNames EnumValue);
};
