// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BodyCleanup/Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "UObject/Object.h"
#include "MorsAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UMorsAnimInstance : public UPlayerCharacterAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void UpdateEnterAnimation(EAnimationType InputAnimationType);
	virtual void UpdateLeftAnimation(EAnimationType InputAnimationType);
	virtual void UpdateCompleteAnimation(EAnimationType InputAnimationType);
	virtual void UpdateAnimationType(EAnimationType NextAnimationType, EAnimationType BeforeAnimationType) override;
};
