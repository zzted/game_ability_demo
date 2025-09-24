// ZZ

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * @class AAuraEnemy
 * @brief Represents an enemy character in the Aura game, inheriting from AAuraCharactorBase and implementing the IEnemyInterface.
 *
 * This class is responsible for defining behavior specific to enemy characters, including highlighting and un-highlighting
 * functionality as part of the implemented IEnemyInterface. It also initializes its own Ability System Component and Attribute Set
 * for gameplay-related features.
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
