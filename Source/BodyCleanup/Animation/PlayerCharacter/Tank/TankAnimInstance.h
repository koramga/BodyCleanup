// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerCharacterAnimInstance.h"
#include "TankAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UTankAnimInstance : public UPlayerCharacterAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void UpdateEnterAnimation(EAnimationType InputAnimationType) override;
	virtual void UpdateLeftAnimation(EAnimationType InputAnimationType) override;
	virtual void UpdateCompleteAnimation(EAnimationType InputAnimationType) override;
	
};
