// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAnimationStateInfo
{
	GENERATED_BODY()

	FAnimationStateInfo()
		: AnimationState(EAnimationState::Left), Duration(0.f)
	{
		
	}
	FAnimationStateInfo(EAnimationState InAnimiationState)
		: AnimationState(InAnimiationState), Duration(0.f)
	{
		
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAnimationState  AnimationState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Duration;
};

UCLASS()
class BODYCLEANUP_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float	MoveBlendSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float	MoveBlendAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<enum EMovementMode> MovementMode;

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAnimationType	DesiredAnimationType = EAnimationType::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAnimationType	AnimationType = EAnimationType::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FAnimationStateInfo>	AnimationStateInfos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float					AnimationPlayTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float					AnimationDurationTime;

private :
	void __OnMontageLeft(UAnimMontage* AnimMontage, bool bIsInterrupt);

protected :
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected :
	virtual void UpdateEnterAnimation(EAnimationType InputAnimationType);
	virtual void UpdateLeftAnimation(EAnimationType InputAnimationType);
	virtual void UpdateCompleteAnimation(EAnimationType InputAnimationType);
	virtual void UpdateAnimationType(EAnimationType NextAnimationType, EAnimationType BeforeAnimationType);
	virtual void OnMontageLeft(UAnimMontage* AnimMontage, bool bIsInterrupt);
	virtual void OnMontagePlay(UAnimMontage* AnimMontage);
	virtual void OnMontageUpdateFromKey(EInputEvent InputEvent);

protected:
	UFUNCTION(BlueprintCallable)
	void EnterAnimationType(EAnimationType InputAnimationType);
	UFUNCTION(BlueprintCallable)
	void LeftAnimationType(EAnimationType InputAnimationType);
	UFUNCTION(BlueprintCallable)
	void CompleteAnimationType(EAnimationType InputAnimationType);

public :
	void SetMoveBlendSpeed(float InputMoveBlendSpeed);
	void SetMoveBlendAngle(float InputMoveBlendAngle);
	void SetMovementMode(EMovementMode InputMovementMode);
	
	void SetAnimationType(EAnimationType InputAnimationType);
	void SetAnimationMontage(UAnimMontage* AnimMontage);
	bool IsPlayingMontage(UAnimMontage* AnimMontage);
	bool IsActivateMontage(UAnimMontage* AnimMontage);
	void SetStopAnimationMontage(UAnimMontage* AnimMontage);
	void UpdateMontageFromKey(EInputEvent InputEvent);
	void SetAnimationDruationTime(EAnimationType InAnimationType, float InAnimationDurationTime);

public :
	virtual bool CanMove() const;
	virtual bool CanUpdateAnimationType(EAnimationType InAnimationType) const;

public :
	EAnimationType GetAnimationType() const;
	EAnimationType GetDesiredAnimationType() const;
	EAnimationState GetAnimationState(EAnimationType InputAnimationType) const;
};
