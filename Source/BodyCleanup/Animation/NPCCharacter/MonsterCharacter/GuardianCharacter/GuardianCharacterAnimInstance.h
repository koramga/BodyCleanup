// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Animation/NPCCharacter/MonsterCharacter/MonsterCharacterAnimInstance.h"
#include "GuardianCharacterAnimInstance.generated.h"

/**
 * 
*/

UCLASS()
class BODYCLEANUP_API UGuardianCharacterAnimInstance : public UMonsterCharacterAnimInstance
{
	GENERATED_BODY()

public :
	UGuardianCharacterAnimInstance();
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	
};
