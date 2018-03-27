// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUp.h"


// Sets default values
APowerUp::APowerUp()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
}
