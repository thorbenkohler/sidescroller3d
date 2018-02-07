// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Collectable.h"
#include "SideScrollerDelegates.generated.h"

UCLASS()
class SIDESCROLLER_API USideScrollerDelegates : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableAdded, ACollectable*);
	static FOnCollectableAdded OnCollectableAdded;
};
