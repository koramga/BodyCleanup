// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "../Character/BaseCharacter.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AnimationStateInfos.Empty();

	int32 AnimationTypeCount = GetMaxEnumValue<EAnimationType>() + 1;

	for(int i = 0; i < AnimationTypeCount; ++i)
	{
		AnimationStateInfos.Add(FAnimationStateInfo());
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(AnimationDurationTime > 0.f)
	{
		AnimationPlayTime += DeltaSeconds;		
	}
	
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UBaseAnimInstance::UpdateEnterAnimation(EAnimationType InputAnimationType)
{
	AnimationPlayTime = 0.f;
	
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (IsValid(BaseCharacter))
	{
		BaseCharacter->UpdateAnimationType(InputAnimationType, AnimationType);
	}

	//변경에 대해서 예고하고
	UpdateAnimationType(InputAnimationType, AnimationType);
}

void UBaseAnimInstance::UpdateLeftAnimation(EAnimationType InputAnimationType)
{
	AnimationDurationTime = AnimationStateInfos[static_cast<int32>(InputAnimationType)].Duration;
}

void UBaseAnimInstance::UpdateCompleteAnimation(EAnimationType InputAnimationType)
{
}

void UBaseAnimInstance::UpdateAnimationType(EAnimationType NextAnimationType, EAnimationType BeforeAnimationType)
{
	AnimationType = NextAnimationType;
}

void UBaseAnimInstance::OnMontageLeft(UAnimMontage* AnimMontage, bool bIsInterrupt)
{
	
}

void UBaseAnimInstance::EnterAnimationType(EAnimationType InputAnimationType)
{
	AnimationStateInfos[static_cast<int32>(InputAnimationType)].AnimationState = EAnimationState::Enter;

	UpdateEnterAnimation(InputAnimationType);
}

void UBaseAnimInstance::LeftAnimationType(EAnimationType InputAnimationType)
{
	if (DesiredAnimationType == InputAnimationType)
	{
		//같은 애니메이션을 소유하고 있다면 Idle로 변경해버린다.
		DesiredAnimationType = EAnimationType::Idle;
	}

	AnimationStateInfos[static_cast<int32>(InputAnimationType)].AnimationState = EAnimationState::Left;

	
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (IsValid(BaseCharacter))
	{
		BaseCharacter->LeftAnimationType(InputAnimationType);
	}

	UpdateLeftAnimation(InputAnimationType);
}

void UBaseAnimInstance::CompleteAnimationType(EAnimationType InputAnimationType)
{
	AnimationStateInfos[static_cast<int32>(InputAnimationType)].AnimationState = EAnimationState::Complete;

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

void UBaseAnimInstance::__OnMontageLeft(UAnimMontage* AnimMontage, bool bIsInterrupt)
{
	OnMontageLeft(AnimMontage, bIsInterrupt);

	LeftAnimationType(AnimationType);
}

void UBaseAnimInstance::SetAnimationMontage(UAnimMontage* AnimMontage)
{
	if(IsValid(AnimMontage))
	{
		Montage_Play(AnimMontage);
		
		FOnMontageEnded BlendEnded;
		BlendEnded.BindUObject(this, &UBaseAnimInstance::__OnMontageLeft);

		Montage_SetEndDelegate(BlendEnded, AnimMontage);
	}	
}

bool UBaseAnimInstance::IsPlayingMontage(UAnimMontage* AnimMontage)
{	
	return Montage_IsPlaying(AnimMontage);
}

bool UBaseAnimInstance::IsActivateMontage(UAnimMontage* AnimMontage)
{
	return Montage_IsActive(AnimMontage);
}

void UBaseAnimInstance::SetStopAnimationMontage(UAnimMontage* AnimMontage)
{
	if(Montage_IsPlaying(AnimMontage))
	{
		Montage_Stop(0.1f, AnimMontage);
	}	
}

void UBaseAnimInstance::SetAnimationDruationTime(EAnimationType InAnimationType, float InAnimationDurationTime)
{
	AnimationStateInfos[static_cast<int32>(InAnimationType)].Duration = InAnimationDurationTime;
}

bool UBaseAnimInstance::CanMove() const
{
	return true;
}

bool UBaseAnimInstance::CanUpdateAnimationType(EAnimationType InAnimationType) const
{
	if(EAnimationType::Death == AnimationType)
	{
		return false;
	}
	else if(EAnimationType::Stun == AnimationType)
	{
		if(EAnimationType::Death == InAnimationType)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

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
	return AnimationStateInfos[static_cast<int32>(InputAnimationType)].AnimationState;
}
