// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundTool/SoundToolMetaData.h"
#include "SoundWaveToolMetaData.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDESIGNERTOOLS_API USoundWaveToolMetaData : public USoundToolMetaData
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Basic")
	FName	ToolName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Basic")
	USoundWave * SoundWave;


};
