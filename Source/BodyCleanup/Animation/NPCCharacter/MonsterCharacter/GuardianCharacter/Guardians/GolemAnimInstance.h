// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Animation/NPCCharacter/MonsterCharacter/GuardianCharacter/GuardianCharacterAnimInstance.h"
#include "GolemAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UGolemAnimInstance : public UGuardianCharacterAnimInstance
{
	GENERATED_BODY()

public :
	UGolemAnimInstance();
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	
};
