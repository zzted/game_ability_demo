// ZZ


#include "AuraCharactorBase.h"

// Sets default values
AAuraCharactorBase::AAuraCharactorBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAuraCharactorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuraCharactorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAuraCharactorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

