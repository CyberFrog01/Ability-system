// Copyright CyberFrog


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbiltyInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	 for (const FAuraInputAction& Action: AbilityInputActions)
	 {
		 if (Action.InputAction && Action.InputTag == InputTag)
		 {
			 return Action.InputAction;
		 }
	 }

	 if (bLogNotFound)
	 {
		 UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputTag for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	 }

	return nullptr;
}
