// ZZ


#include "Actor/AuraFireBall.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayCueManager.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"

void AAuraFireBall::ExecuteImpactFXs() 
{
	if (GetOwner())
	{
		FGameplayCueParameters CueParams;
		CueParams.Location = GetActorLocation();
		// Execute gameplay cue locally when something is already replicated
		UGameplayCueManager::ExecuteGameplayCue_NonReplicated(GetOwner(), FAuraGameplayTags::Get().GameplayCue_FireBlast, CueParams);
	}
	bHit = true;
}

void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	StartOutgoingTimeline();
}

void AAuraFireBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const AActor* ThisOwner = GetOwner();
	if (!IsValid(ThisOwner))
	{
		bHit = true;
		Destroy();
		return;
	}

	if (OtherActor == ThisOwner) return;
	if (!UAuraAbilitySystemLibrary::IsNotFriend(OtherActor, ThisOwner)) return;

	if (HasAuthority())
	{
		// NOTE: DamageEffectSpecHandle should be valid only on the server (we set it there but also don't replicate it).
		
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;
			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			
			UAuraAbilitySystemLibrary::ApplyDamageEffectsFromDamageEffectParams(DamageEffectParams);
		}
	}
}
