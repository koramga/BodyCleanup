// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseAnimInstance.h"
#include "NPCCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UNPCCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()

public :
	UNPCCharacterAnimInstance();
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	
};
