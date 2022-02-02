// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacterAnimInstance.h"

UNPCCharacterAnimInstance::UNPCCharacterAnimInstance()
{
}

void UNPCCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UNPCCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UNPCCharacterAnimInstance::UpdateAnimationType(EAnimationType NextAnimationType,
	EAnimationType BeforeAnimationType)
{
	Super::UpdateAnimationType(NextAnimationType, BeforeAnimationType);
}
