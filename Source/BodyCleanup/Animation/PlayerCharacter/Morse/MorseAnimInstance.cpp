// Fill out your copyright notice in the Description page of Project Settings.


#include "MorseAnimInstance.h"

void UMorseAnimInstance::UpdateEnterAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateEnterAnimation(InputAnimationType);
}

void UMorseAnimInstance::UpdateLeftAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateLeftAnimation(InputAnimationType);
}

void UMorseAnimInstance::UpdateCompleteAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateCompleteAnimation(InputAnimationType);
}

void UMorseAnimInstance::UpdateAnimationType(EAnimationType NextAnimationType, EAnimationType BeforeAnimationType)
{
	Super::UpdateAnimationType(NextAnimationType, BeforeAnimationType);

	if(EAnimationType::Shot == BeforeAnimationType
		|| EAnimationType::Vacuum == BeforeAnimationType)
	{
		bIsShot = false;
	}
}

void UMorseAnimInstance::SetShot()
{
	bIsShot = true;
}

bool UMorseAnimInstance::IsShot() const
{
	return bIsShot;
}
