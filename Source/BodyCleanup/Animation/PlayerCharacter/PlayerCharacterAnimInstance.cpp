// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

bool UPlayerCharacterAnimInstance::CanMove() const
{
	if (EAnimationType::Wait == AnimationType)
	{
		return false;
	}

	return Super::CanMove();
}

void UPlayerCharacterAnimInstance::SetMoveOffset(int32 InputMoveOffset)
{
	MoveOffset = InputMoveOffset;
}
