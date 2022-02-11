// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundToolsManager.generated.h"

/**
 * 
 */

USTRUCT()
struct FSoundToolItem
{
	GENERATED_BODY();

	UPROPERTY()
	class UAudioComponent* AudioComponent;

	UPROPERTY()
		FName	Name;

	UPROPERTY()
		float  FadeOutTime;
};

USTRUCT()
struct FSoundToolItemList
{
	GENERATED_BODY();

	UPROPERTY()
	TArray<FSoundToolItem>	SoundToolItemList;
};

UCLASS()
class SOUNDDESIGNERTOOLS_API USoundToolsManager : public UObject
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	TMap<FName, FSoundToolItemList>	SoundToolItemLists;

public :
	bool AddAudioComponent(const FName& InName, class UAudioComponent* InAudioComponent, float InFadeOutTime);
	bool RemoveAudioComponents(const FName& InName);
};
