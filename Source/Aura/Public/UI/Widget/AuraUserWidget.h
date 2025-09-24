// ZZ

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * UAuraUserWidget is a custom user widget class that extends UUserWidget.
 * It is designed to manage and interact with a WidgetController, enabling dynamic runtime logic
 * for widgets in a game application. This WidgetController is blueprint-compatible, allowing for
 * easy integration and use within the Unreal Engine Editor and Blueprints.
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetWidgetController(UObject* InWidgetController);

	
	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
