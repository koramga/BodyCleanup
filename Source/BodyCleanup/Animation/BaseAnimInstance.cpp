// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "../Character/BaseCharacter.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AnimationStates.Empty();

	int32 AnimationTypeCount = GetMaxEnumValue<EAnimationType>() + 1;

	for (int i = 0; i < AnimationTypeCount; ++i)
	{
		AnimationStates.Add(EAnimationState::Left);
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UBaseAnimInstance::UpdateEnterAnimation(EAnimationType InputAnimationType)
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (IsValid(BaseCharacter))
	{
		BaseCharacter->UpdateAnimationType(InputAnimationType, AnimationType);
	}

	AnimationType = InputAnimationType;
}

void UBaseAnimInstance::UpdateLeftAnimation(EAnimationType InputAnimationType)
{
}

void UBaseAnimInstance::UpdateCompleteAnimation(EAnimationType InputAnimationType)
{
}

void UBaseAnimInstance::EnterAnimationType(EAnimationType InputAnimationType)
{
	AnimationStates[static_cast<int32>(InputAnimationType)] = EAnimationState::Enter;

	UpdateEnterAnimation(InputAnimationType);
}

void UBaseAnimInstance::LeftAnimationType(EAnimationType InputAnimationType)
{
	if (DesiredAnimationType == InputAnimationType)
	{
		//같은 애니메이션을 소유하고 있다면 Idle로 변경해버린다.
		DesiredAnimationType = EAnimationType::Idle;
	}

	AnimationStates[static_cast<int32>(InputAnimationType)] = EAnimationState::Left;

	UpdateLeftAnimation(InputAnimationType);
}

void UBaseAnimInstance::CompleteAnimationType(EAnimationType InputAnimationType)
{
	AnimationStates[static_cast<int32>(InputAnimationType)] = EAnimationState::Complete;

	UpdateCompleteAnimation(InputAnimationType);
}

void UBaseAnimInstance::SetMoveBlendSpeed(float InputMoveBlendSpeed)
{
	MoveBlendSpeed = InputMoveBlendSpeed;
}

void UBaseAnimInstance::SetMoveBlendAngle(float InputMoveBlendAngle)
{
	MoveBlendAngle = InputMoveBlendAngle;
}

void UBaseAnimInstance::SetMovementMode(EMovementMode InputMovementMode)
{
	MovementMode = InputMovementMode;
}

void UBaseAnimInstance::SetAnimationType(EAnimationType InputAnimationType)
{
	DesiredAnimationType = InputAnimationType;
}

bool UBaseAnimInstance::CanMove() const
{
	return true;
}

EAnimationType UBaseAnimInstance::GetAnimationType() const
{
	return AnimationType;
}

EAnimationType UBaseAnimInstance::GetDesiredAnimationType() const
{
	return DesiredAnimationType;
}

EAnimationState UBaseAnimInstance::GetAnimationState(EAnimationType InputAnimationType) const
{
	return AnimationStates[static_cast<int32>(InputAnimationType)];
}
