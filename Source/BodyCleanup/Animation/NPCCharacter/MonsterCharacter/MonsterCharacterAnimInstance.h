// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../NPCCharacterAnimInstance.h"
#include "MonsterCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UMonsterCharacterAnimInstance : public UNPCCharacterAnimInstance
{
	GENERATED_BODY()

public :
	UMonsterCharacterAnimInstance();
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;		
};
