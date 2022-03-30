// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationDesignerTools/AnimationDesignerToolsDefines.h"
#include "UObject/Interface.h"

#include "AnimationToolsActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAnimationToolsActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ANIMATIONDESIGNERTOOLS_API IAnimationToolsActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnChangeOfStateFromNotify(FAnimNotify_ChangeOfStateStruct& InNotifyStruct) = 0;
	virtual void OnCreateActorFromNotify(TWeakObjectPtr<AActor> Actor) = 0;
};
