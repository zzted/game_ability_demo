#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

// Helper: 获取当前实例的身份（Server/Client）
// FString GetNetIdentity(const UObject* Obj)
// {
//     if (!Obj) return TEXT("Unknown");
//
//     const AActor* Actor = Cast<AActor>(Obj);
//     if (!Actor) return TEXT("NoActor");
//
//     ENetRole Role = Actor->GetLocalRole();
//     FString RoleStr = 
//         Role == ROLE_Authority ? TEXT("SERVER") :
//         Role == ROLE_AutonomousProxy ? TEXT("CLIENT_OWNED") :
//         Role == ROLE_SimulatedProxy ? TEXT("CLIENT_SIMULATED") :
//         TEXT("UNKNOWN");
//
//     return FString::Printf(TEXT("%s (Role=%d)"), *RoleStr, (int)Role);
// }

UPassiveNiagaraComponent::UPassiveNiagaraComponent()
{
	bAutoActivate = false;
}

void UPassiveNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	// FString Identity = GetNetIdentity(GetOwner());
	//
	// UE_LOG(LogTemp, Warning,
	// 	TEXT("[BeginPlay][%s] PassiveNiagara '%s' BeginPlay on Owner '%s'"),
	// 	*Identity,
	// 	*GetNameSafe(this),
	// 	*GetNameSafe(GetOwner()));

	// --- 直接从 ASC 获取 ---
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())))
	{
		AuraASC->ActivatePassiveEffect.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
		ActivateIfEquipped(AuraASC); // Could have missed broadcast when the niagara system construct, so check if the passive has been equipped
	}

	// --- 延迟：通过 CombatInterface 注册 ---
	else if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner()))
	{
		CombatInterface->GetOnASCRegisteredDelegate().AddLambda(
			[this](UAbilitySystemComponent* ASC)
			{
				if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(ASC))
				{
					AuraASC->ActivatePassiveEffect.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
					ActivateIfEquipped(AuraASC);
				}
			}
		);
	}
}

void UPassiveNiagaraComponent::OnPassiveActivate(const FGameplayTag& AbilityTag, bool bActivate)
{
	// FString Identity = GetNetIdentity(GetOwner());
	//
	// UE_LOG(LogTemp, Warning,
	// 	TEXT("[PassiveActivate][%s] Component '%s' Got Event: %s -> %d, IsActive=%d"),
	// 	*Identity,
	// 	*GetNameSafe(this),
	// 	*AbilityTag.ToString(),
	// 	bActivate,
	// 	IsActive());

	if (AbilityTag.MatchesTagExact(PassiveSpellTag))
	{
		if (bActivate && !IsActive())
		{
			// UE_LOG(LogTemp, Warning,
			// 	TEXT("[PassiveActivate][%s] Activating Niagara '%s'"),
			// 	*Identity, *GetNameSafe(this));

			Activate();
		}
		else if (!bActivate && IsActive())
		{
			// UE_LOG(LogTemp, Warning,
			// 	TEXT("[PassiveActivate][%s] Deactivating Niagara '%s'"),
			// 	*Identity, *GetNameSafe(this));

			Deactivate();
		}
	}
}

void UPassiveNiagaraComponent::ActivateIfEquipped(UAuraAbilitySystemComponent* AuraASC)
{
	if (AuraASC->bStartupAbilitiesGiven)
	{
		if (AuraASC->GetStatusTagFromAbilityTag(PassiveSpellTag) == FAuraGameplayTags::Get().Abilities_Status_Equipped)
		{
			Activate();
		}
	}
}