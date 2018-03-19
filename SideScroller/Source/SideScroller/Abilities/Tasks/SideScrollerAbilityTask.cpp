// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerAbilityTask.h"



USideScrollerAbilityTask::USideScrollerAbilityTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


USideScrollerAbilityTask* USideScrollerAbilityTask::CreateMyTask(UGameplayAbility* OwningAbility, FName TaskInstanceName, float ExampleVariable)
{

	USideScrollerAbilityTask* SideScrollerAbilityTask = NewAbilityTask<USideScrollerAbilityTask>(OwningAbility, TaskInstanceName);
	//Just assume we have defined a float called OptionalValue somewhere in the class before. This is just an example.
	SideScrollerAbilityTask->OptionalValue = ExampleVariable;

	return SideScrollerAbilityTask;
}

void USideScrollerAbilityTask::Activate()
{
	// This is the part where you'd set up different delegates, timers etc. to prepare the task
	// to eventually broadcast OnAbilityTaskDelegate sometime later. We have nothing prepared in this tutorial
	// task however, so we may as well just call OnAbilityTaskDelegate right within the Activate function instead. 
	FAbilityTaskData AbilityTaskData;
	AbilityTaskData.TestValue = 2.0f;
	AbilityTaskData.AnotherTestValue = 5;
	OnAbilityTaskDelegate.Broadcast(AbilityTaskData);
}
