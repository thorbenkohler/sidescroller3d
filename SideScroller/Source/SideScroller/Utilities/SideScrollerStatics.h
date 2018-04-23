// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SideScrollerGameMode.h"
#include "SideScrollerStatics.generated.h"

/**
*
*/
UCLASS()
class SIDESCROLLER_API USideScrollerStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Get the current game mode, pre-cast to ASideScrollerGameMode for convenience. */
	UFUNCTION(BlueprintCallable, Category = "SideScroller")
	static class ASideScrollerGameMode* GetSideScrollerGameMode(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "SideScroller")
	static TArray<UObject*> LoadObjectLibrary(const FString& Path, TSubclassOf<UObject> ObjectClass);

	/** Gets the last single name of the specified Tag. */
	UFUNCTION(BlueprintPure, Category = "SideScroller")
	static FName GetLastTagName(FGameplayTag Tag);
};
