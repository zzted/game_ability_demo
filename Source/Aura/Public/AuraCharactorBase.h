// ZZ

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharactorBase.generated.h"

UCLASS()
class AURA_API AAuraCharactorBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharactorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
