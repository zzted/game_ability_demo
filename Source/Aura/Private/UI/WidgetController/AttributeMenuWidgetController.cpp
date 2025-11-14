// ZZ


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);;

	for (auto& Pair : GetAuraAS()->TagsToAttributes)
	{
		// Deprecated delegate method
		// Info.AttributeValue = Pair.Value.Execute().GetNumericValue(AuraAttributeSet);
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	
	AttributePointsDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	SpellPointsDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	for (auto& Pair : GetAuraAS()->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
	
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
	[this](const int32 NewValue)
	{
		AttributePointsDelegate.Broadcast(NewValue);
	}
);

	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](const int32 NewValue)
		{
			SpellPointsDelegate.Broadcast(NewValue);
		}
	);
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	GetAuraASC()->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                            const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
