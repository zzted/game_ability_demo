// ZZ


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (FAuraInputAction AuraInputAction : AbilityInputActions)
	{
		if (AuraInputAction.InputAction && AuraInputAction.InputTag.MatchesTagExact(InputTag))
		{
			return AuraInputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find AbilityInputAction action for InputTag [%s], on AuraInputConfig %s"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
