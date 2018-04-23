#include "DamageAttributeSet.h"
#include "SideScroller.h"
 
const float UDamageAttributeSet::MAX_DAMAGE = TNumericLimits<float>::Max();
   
const FGameplayAttribute& UDamageAttributeSet::DamageAttribute()
{
    static FGameplayAttribute Attribute(FindFieldChecked<UProperty>(
        UDamageAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UDamageAttributeSet, Damage)));
    return Attribute;
}

void UDamageAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == DamageAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MAX_DAMAGE);
	}
}

void UDamageAttributeSet::PostInitializeProperties(bool bInitialInit)
{

}
