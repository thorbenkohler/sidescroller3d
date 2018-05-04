#include "HealthAttributeSet.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/SideScrollerCharacter.h"
#include "Utilities/SideScrollerDelegates.h"
#include "Interfaces/HealthInterface.h"
#include "SideScroller.h"
 
const float UHealthAttributeSet::MAX_HEALTH = TNumericLimits<float>::Max();
   
const FGameplayAttribute& UHealthAttributeSet::MaxHealthAttribute()
{
    static FGameplayAttribute Attribute(FindFieldChecked<UProperty>(
        UHealthAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UHealthAttributeSet, MaxHealth)));
    return Attribute;
}

const FGameplayAttribute& UHealthAttributeSet::HealthAttribute()
{
    static FGameplayAttribute Attribute(FindFieldChecked<UProperty>(
        UHealthAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UHealthAttributeSet, Health)));
    return Attribute;
}

void UHealthAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == MaxHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MAX_HEALTH);
	}

	if (Attribute == HealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxHealth);
	}
}

void UHealthAttributeSet::PostInitializeProperties(bool bInitialInit)
{
	if (bInitialInit)
	{
		Health = MaxHealth;
	}
}
