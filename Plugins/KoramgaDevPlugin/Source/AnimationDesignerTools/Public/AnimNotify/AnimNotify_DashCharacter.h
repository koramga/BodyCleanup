// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DashCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONDESIGNERTOOLS_API UAnimNotify_DashCharacter : public UAnimNotify
{
	GENERATED_BODY()

public :
	UAnimNotify_DashCharacter();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	LaunchPower = 1000.f;
};


