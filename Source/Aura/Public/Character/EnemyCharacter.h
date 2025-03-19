// Copyright CyberFrog

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/MouseoverInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ACharacterBase, public IMouseoverInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	/** Mouseover Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Mouseover Interface */

	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface */
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	
};
