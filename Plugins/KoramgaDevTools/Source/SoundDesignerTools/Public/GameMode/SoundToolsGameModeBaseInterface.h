// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoundToolsGameModeBaseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USoundToolsGameModeBaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOUNDDESIGNERTOOLS_API ISoundToolsGameModeBaseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TSoftObjectPtr<class USoundToolsManager> GetSoundToolsManager() = 0;
};
