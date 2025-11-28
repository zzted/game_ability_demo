// ZZ


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 Damage = DamageAmount.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float CoolDown = GetCooldown(Level);

	return FString::Printf(TEXT(""
						  "<Title>FIRE BLAST</>\n\n"
						  
						  "<Small>Level: </><Level>%d</>\n"
						  "<Small>Mana Cost: </><ManaCost>%.1f</>\n" // %.1f will have only one decimal
						  "<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
						  
						  "<Default>Launches %d fire balls in all direction, "
						  "each coming back and exploding upon return, "
						  "causing: </> <Damage>%d</> <Default> radial fire damage with a chance to burn</>\n\n"
						  ),  Level, ManaCost, CoolDown, NumFireBalls, Damage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = DamageAmount.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float CoolDown = GetCooldown(Level);

	return FString::Printf(TEXT(""
						  "<Title>NEXT LEVEL:</>\n\n"
						  
						  "<Small>Level: </><Level>%d</>\n"
						  "<Small>Mana Cost: </><ManaCost>%.1f</>\n" // %.1f will have only one decimal
						  "<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
						  
						  "<Default>Launches %d fire balls in all direction, "
						  "each coming back and exploding upon return, "
						  "causing: </> <Damage>%d</> <Default> radial fire damage with a chance to burn</>\n\n"
						  ),  Level, ManaCost, CoolDown, NumFireBalls, Damage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	return TArray<AAuraFireBall*>();
}
