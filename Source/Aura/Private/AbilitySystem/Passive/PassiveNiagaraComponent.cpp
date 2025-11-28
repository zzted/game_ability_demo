#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

// Helper: 获取当前实例的身份（Server/Client）
FString GetNetIdentity(const UObject* Obj)
{
    if (!Obj) return TEXT("Unknown");

    const AActor* Actor = Cast<AActor>(Obj);
    if (!Actor) return TEXT("NoActor");

    ENetRole Role = Actor->GetLocalRole();
    FString RoleStr = 
        Role == ROLE_Authority ? TEXT("SERVER") :
        Role == ROLE_AutonomousProxy ? TEXT("CLIENT_OWNED") :
        Role == ROLE_SimulatedProxy ? TEXT("CLIENT_SIMULATED") :
        TEXT("UNKNOWN");

    return FString::Printf(TEXT("%s (Role=%d)"), *RoleStr, (int)Role);
}

UPassiveNiagaraComponent::UPassiveNiagaraComponent()
{
	bAutoActivate = false;
}

void UPassiveNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	FString Identity = GetNetIdentity(GetOwner());

	UE_LOG(LogTemp, Warning,
		TEXT("[BeginPlay][%s] PassiveNiagara '%s' BeginPlay on Owner '%s'"),
		*Identity,
		*GetNameSafe(this),
		*GetNameSafe(GetOwner()));

	// --- 直接从 ASC 获取 ---
	if (UAuraAbilitySystemComponent* AuraASC =
		Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[DelegateRegistration][%s] Registering directly with ASC: %s"),
			*Identity,
			*GetNameSafe(AuraASC));

		AuraASC->ActivatePassiveEffect.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
		return;
	}

	// --- 延迟：通过 CombatInterface 注册 ---
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner()))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[DelegateRegistration][%s] Waiting ASC registration through CombatInterface..."),
			*Identity);

		CombatInterface->GetOnASCRegisteredDelegate().AddLambda(
			[this, Identity](UAbilitySystemComponent* ASC)
			{
				UAuraAbilitySystemComponent* AuraASC =
					Cast<UAuraAbilitySystemComponent>(ASC);

				UE_LOG(LogTemp, Warning,
					TEXT("[DelegateRegistration][%s] ASC Registered through CombatInterface: %s"),
					*Identity,
					*GetNameSafe(AuraASC));

				if (AuraASC)
				{
					AuraASC->ActivatePassiveEffect.AddUObject(
						this,
						&UPassiveNiagaraComponent::OnPassiveActivate
					);

					UE_LOG(LogTemp, Warning,
						TEXT("[DelegateRegistration][%s] SUCCESS: Delegate bound to %s"),
						*Identity,
						*GetNameSafe(AuraASC));
				}
			}
		);
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("[DelegateRegistration][%s] ERROR: No ASC and No CombatInterface found on Owner '%s'"),
			*Identity,
			*GetNameSafe(GetOwner()));
	}
}

void UPassiveNiagaraComponent::OnPassiveActivate(const FGameplayTag& AbilityTag, bool bActivate)
{
	FString Identity = GetNetIdentity(GetOwner());

	UE_LOG(LogTemp, Warning,
		TEXT("[PassiveActivate][%s] Component '%s' Got Event: %s -> %d, IsActive=%d"),
		*Identity,
		*GetNameSafe(this),
		*AbilityTag.ToString(),
		bActivate,
		IsActive());

	if (AbilityTag.MatchesTagExact(PassiveSpellTag))
	{
		if (bActivate && !IsActive())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("[PassiveActivate][%s] Activating Niagara '%s'"),
				*Identity, *GetNameSafe(this));

			Activate();
		}
		else if (!bActivate && IsActive())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("[PassiveActivate][%s] Deactivating Niagara '%s'"),
				*Identity, *GetNameSafe(this));

			Deactivate();
		}
	}
}