// ZZ


#include "AbilitySystem/AuraAbilitySystemGlobals.h"

#include "AuraAbilitySystemTypes.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
