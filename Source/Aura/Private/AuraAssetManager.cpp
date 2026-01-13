// ZZ


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	// FAuraGameplayTags::InitializeNativeGameplayTags(); Was called here but is causing a problem that the tags are not initialized when DamageStatics is constructed. changed to a singleton type initialization.

	//UAbilitySystemGlobals::Get().InitGlobalData();  TargetDataStructCache init, required for using target data. no need to call that after UE 5.3 https://github.com/tranek/GASDocumentation?tab=readme-ov-file#491-initglobaldata
}
