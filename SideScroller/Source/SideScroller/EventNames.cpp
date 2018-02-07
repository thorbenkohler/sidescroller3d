// Fill out your copyright notice in the Description page of Project Settings.

#include "EventNames.h"
#include "Kismet/GameplayStatics.h"


FString UEventNames::GetEventNameAsString(EEventNames EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEventNames"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetNameByValue((int64)EnumValue).ToString();
}
