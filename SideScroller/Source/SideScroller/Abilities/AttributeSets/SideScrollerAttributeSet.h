// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "SideScrollerAttributeSet.generated.h"


UCLASS(BlueprintType)
class USideScrollerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void PostInitializeProperties(bool bInitialInit);
};
