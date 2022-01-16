// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseAnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UPlayerCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32	MoveOffset;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public :
	virtual bool CanMove() const override;

public :
	void SetMoveOffset(int32 InputMoveOffset);
};
