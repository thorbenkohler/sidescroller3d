// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerDelegates.generated.h"

class ACollectable;
class AWeapon;

UCLASS()
class SIDESCROLLER_API USideScrollerDelegates : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableAdded, ACollectable*);
	static FOnCollectableAdded OnCollectableAdded;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableWeaponAdded, AWeapon*);
	static FOnCollectableWeaponAdded OnCollectableWeaponAdded;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCollectableCoinAdded, int32);
	static FOnCollectableCoinAdded OnCollectableCoinAdded;
};
