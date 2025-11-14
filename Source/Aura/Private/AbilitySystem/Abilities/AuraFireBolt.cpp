// ZZ


#include "AbilitySystem/Abilities/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	// const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const int32 Damage = DamageAmount.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float CoolDown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(""
							  "<Title>FIRE BOLT</>\n\n"
							  
							  "<Small>Level: </><Level>%d</>\n"
							  "<Small>Mana Cost: </><ManaCost>%.1f</>\n" // %.1f will have only one decimal
							  "<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
							  
							  "<Default>Launches a bolt of fire, exploding on impact and dealing: </> <Damage>%d</> <Default> fire damage with a chance to burn</>\n\n"
							  ),  Level, ManaCost, CoolDown, Damage);
	}
	return FString::Printf(TEXT(""
		"<Title>FIRE BOLT</>\n\n"
		
		"<Small>Level: </><Level>%d</>\n"
		"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		
		"<Default>Launches %d bolts of fire, exploding on impact and dealing: </><Damage>%d</><Default> fire damage with a chance to burn</>\n\n"
		), Level, ManaCost, CoolDown, FMath::Min(Level, NumProjectiles), Damage);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = DamageAmount.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float CoolDown = GetCooldown(Level);
	return FString::Printf(TEXT(""
		"<Title>NEXT LEVEL:</>\n\n"
		
		"<Small>Level: </><Level>%d</>\n"
		"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		
		"<Default>Launches %d bolts of fire, exploding on impact and dealing: </><Damage>%d</><Default> fire damage with a chance to burn</>\n\n"
		), Level, ManaCost, CoolDown, FMath::Min(Level, NumProjectiles), Damage);
}
