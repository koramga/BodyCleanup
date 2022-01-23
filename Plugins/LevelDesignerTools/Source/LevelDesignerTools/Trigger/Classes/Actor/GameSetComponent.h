// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerActorComponent.h"
#include "GameSetComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDESIGNERTOOLS_API UGameSetComponent : public UTriggerActorComponent
{
	GENERATED_BODY()
	
protected :
	virtual void SetupTrigger() override;

};
