// ZZ


#include "Character/AuraCharactorBase.h"

AAuraCharactorBase::AAuraCharactorBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharactorBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharactorBase::BeginPlay()
{
	Super::BeginPlay();
}
