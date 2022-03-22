// Fill out your copyright notice in the Description page of Project Settings.


#include "MorsAnimInstance.h"

void UMorsAnimInstance::UpdateEnterAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateEnterAnimation(InputAnimationType);
}

void UMorsAnimInstance::UpdateLeftAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateLeftAnimation(InputAnimationType);
}

void UMorsAnimInstance::UpdateCompleteAnimation(EAnimationType InputAnimationType)
{
	Super::UpdateCompleteAnimation(InputAnimationType);
}

void UMorsAnimInstance::UpdateAnimationType(EAnimationType NextAnimationType, EAnimationType BeforeAnimationType)
{
	Super::UpdateAnimationType(NextAnimationType, BeforeAnimationType);
}
