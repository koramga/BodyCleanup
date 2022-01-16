// Fill out your copyright notice in the Description page of Project Settings.


#include "MorseAnimInstance.h"

void UMorseAnimInstance::UpdateEnterAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateEnterAnimation(InputAnimationType);

	if (EAnimationType::Shot == InputAnimationType
		|| EAnimationType::Vacuum == InputAnimationType)
	{
		bIsShot = false;
	}
}

void UMorseAnimInstance::UpdateLeftAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateLeftAnimation(InputAnimationType);
}

void UMorseAnimInstance::UpdateCompleteAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateCompleteAnimation(InputAnimationType);
}

void UMorseAnimInstance::SetShot()
{
	bIsShot = true;
}
