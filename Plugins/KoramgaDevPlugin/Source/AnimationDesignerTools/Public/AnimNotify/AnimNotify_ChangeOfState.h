// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimationDesignerTools/AnimationDesignerToolsDefines.h"
#include "AnimNotify_ChangeOfState.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONDESIGNERTOOLS_API UAnimNotify_ChangeOfState : public UAnimNotify
{
	GENERATED_BODY()

public :
	UAnimNotify_ChangeOfState();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FAnimNotify_ChangeOfStateStruct	ChangeOfStateStruct;

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
	
};
