#include "SideScrollerAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "Character/SideScrollerCharacter.h"


   
FGameplayAttribute USideScrollerAttributeSet::HealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(USideScrollerAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(USideScrollerAttributeSet, Health));
	return FGameplayAttribute(Property);
}

FGameplayAttribute USideScrollerAttributeSet::MaxHealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(USideScrollerAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(USideScrollerAttributeSet, MaxHealth));
	return FGameplayAttribute(Property);
}

void USideScrollerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	UAbilitySystemComponent* Source = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();

	if (HealthAttribute() == Data.EvaluatedData.Attribute)
	{
		// Get the Target actor
		AActor* DamagedActor = nullptr;
		AController* DamagedController = nullptr;
		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			DamagedActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
			DamagedController = Data.Target.AbilityActorInfo->PlayerController.Get();
		}

		// Get the Source actor
		AActor* AttackingActor = nullptr;
		AController* AttackingController = nullptr;
		AController* AttackingPlayerController = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			AttackingActor = Source->AbilityActorInfo->AvatarActor.Get();
			AttackingController = Source->AbilityActorInfo->PlayerController.Get();
			AttackingPlayerController = Source->AbilityActorInfo->PlayerController.Get();
			if (AttackingController == nullptr && AttackingActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(AttackingActor))
				{
					AttackingController = Pawn->GetController();
				}
			}
		}

		// Clamp health
		float TempHealth = FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue());
		Health.SetCurrentValue(TempHealth);

		if (TempHealth <= 0)
		{
			// Handle death with GASCharacter. Note this is just one example of how this could be done.
			if (ASideScrollerCharacter* SideScrollerCharacter = Cast<ASideScrollerCharacter>(DamagedActor))
			{
				// Construct a gameplay cue event for this death
				FGameplayCueParameters Params(Data.EffectSpec.GetContext());
				Params.RawMagnitude = Data.EvaluatedData.Magnitude;;
				Params.NormalizedMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude / MaxHealth.GetCurrentValue());
				//Params.AggregatedSourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
				//Params.AggregatedTargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();

				//SideScrollerCharacter->Die(DamagedController, DamagedActor, Data.EffectSpec, Params.RawMagnitude, Params.Normal);
				SideScrollerCharacter->OnDeath();
			}
		}
	}
}