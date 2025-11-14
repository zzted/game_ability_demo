// ZZ


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		//UE_LOG(LogTemp, Error, TEXT("Could not find ability info for tag %s, on AbilityInfo %s"), *AbilityTag.ToString(), *GetNameSafe(this));
		UE_LOG(LogAura, Error, TEXT("Could not find ability info for tag [%s], on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAbilityInfo();
}
