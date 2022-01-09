// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseActor.h"
#include "BaseLevelActor.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseLevelActor : public ABaseActor
{
	GENERATED_BODY()

public :
	ABaseLevelActor();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ULevelComponent* LevelComponent;
	
};
