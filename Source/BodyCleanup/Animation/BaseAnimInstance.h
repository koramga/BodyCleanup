// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
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
	EAnimationType	DesiredAnimationType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAnimationType	AnimationType;

	UPROPERTY(VisibleAnywhere, BlueprintREadonly)
	TArray<EAnimationState>	AnimationStates;

protected :
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected :
	virtual void UpdateEnterAnimation(EAnimationType InputAnimationType);
	virtual void UpdateLeftAnimation(EAnimationType InputAnimationType);
	virtual void UpdateCompleteAnimation(EAnimationType InputAnimationType);

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

public :
	EAnimationType GetAnimationType() const;
	EAnimationType GetDesiredAnimationType() const;
	EAnimationState GetAnimationState(EAnimationType InputAnimationType) const;
};
