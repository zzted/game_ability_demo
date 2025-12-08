// ZZ


#include "AbilitySystem/Abilities/AuraFireBlast.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"

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
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetAvatarActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();

		FireBall->ExplosionDamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->SetOwner(GetAvatarActorFromActorInfo());

		FireBalls.Add(FireBall);

		FireBall->FinishSpawning(SpawnTransform);
	}
	
	return FireBalls;
}
