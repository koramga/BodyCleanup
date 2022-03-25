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
	
protected:
	FName				MontageCurrentSectionName;
	FName				MontageNextSectionName;
	float				EnergyHoldingTime;
	FName				NextSectionName;
	FName				PressedSectionName;
	FName				ReleasedSectionName;
	FName				ExecuteSectionName;
	FVector				ExecutionLocation;

protected:
	void UpdateMontage(float DeltaSeconds);
	virtual void OnMontageUpdateFromKey(EInputEvent InputEvent) override;
	void ChangeMontageSection(FName InputMontageNextSectionName, bool bJumpToSection = false);
	bool CanChangeMontageSection() const;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public :
	virtual bool CanMove() const override;
	virtual void OnMontagePlay(UAnimMontage* AnimMontage) override;

public :
	void SetMoveOffset(int32 InputMoveOffset);
};
