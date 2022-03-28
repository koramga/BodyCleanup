// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundTool/SoundToolDataAsset.h"
#include "SoundDesignerToolsDefines.h"
#include "SoundWaveToolDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDESIGNERTOOLS_API USoundWaveToolDataAsset : public USoundToolDataAsset
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TurnOn")
	TArray<FSoundWave2DInfo>	SoundWave2DInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TurnOn")
	TArray<FSoundWave3DInfo>	SoundWave3DInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TurnOff")
	TArray<FName>				SoundWaveTurnOffNames;

public :
	const TArray<FSoundWave2DInfo>& GetSoundWave2DInfos() const;
	const TArray<FSoundWave3DInfo>& GetSoundWave3DInfos() const;
	const TArray<FName>& GetSoundWaveTurnOffNames() const;

};
