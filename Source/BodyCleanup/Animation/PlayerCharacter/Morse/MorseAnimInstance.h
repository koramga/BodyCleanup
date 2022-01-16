// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerCharacterAnimInstance.h"
#include "MorseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UMorseAnimInstance : public UPlayerCharacterAnimInstance
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsShot = false;

protected:
	virtual void UpdateEnterAnimation(EAnimationType InputAnimationType);
	virtual void UpdateLeftAnimation(EAnimationType InputAnimationType);
	virtual void UpdateCompleteAnimation(EAnimationType InputAnimationType);

public :
	void SetShot();

};
