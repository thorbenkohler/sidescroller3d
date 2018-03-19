// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SideScrollerAbilityTask.generated.h"


// Used as event data structure
USTRUCT()
struct FAbilityTaskData
{
	GENERATED_BODY()

public:
	float TestValue;

	int32 AnotherTestValue;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskDelegate, FAbilityTaskData, AbilityTaskData);

UCLASS()
class SIDESCROLLER_API USideScrollerAbilityTask : public UAbilityTask
{
	GENERATED_UCLASS_BODY()

public:

	// The important bit here.
	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskDelegate OnAbilityTaskDelegate;

	// This UFUNCTION macro describes, in that order:
	// The function can be called in BP, the category in which
	// the function will de displayed in the BP-function-
	// dropdown is "Ability", subcategory "Tasks", the function
	// name in BP is displayed as "ExecuteMyTask",
	// the pin for the parameter "OwningAbility" is hidden in BP
	// and the parameter "OwningAbility" will default to
	// the object the calling graph belongs to, if applicable.
	// Finally, BlueprintInternalUseOnly = "TRUE" prevents
	// a regular function node for this UFUNCTION to be created,
	// which makes sense because this function needs to use
	// an async task node instead(which has some added behaviour
	// on being called such as actually activating the
	// task, extra exec pins, etc).
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "ExecuteMyTask", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static USideScrollerAbilityTask* CreateMyTask(UGameplayAbility* OwningAbility, FName TaskInstanceName, float ExamplevAriable);

	float OptionalValue;

	// This function will call after the BP node has successfully requested the
	// ability task from the static function. You put your actual functionality here. 
	virtual void Activate() override;
};
