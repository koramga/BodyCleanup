// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterCharacterAnimInstance.h"
#include "MouseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UMouseAnimInstance : public UMonsterCharacterAnimInstance
{
	GENERATED_BODY()
	
public :
	UMouseAnimInstance();
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	
};
