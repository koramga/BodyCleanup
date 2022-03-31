// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Animation/NPCCharacter/MonsterCharacter/MonsterCharacterAnimInstance.h"
#include "RangerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API URangerAnimInstance : public UMonsterCharacterAnimInstance
{
	GENERATED_BODY()
	
public :
	URangerAnimInstance();
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	
};
