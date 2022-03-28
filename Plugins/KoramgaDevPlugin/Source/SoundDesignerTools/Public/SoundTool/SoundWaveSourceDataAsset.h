// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SoundWaveSourceDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSoundWaveSourceGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USoundWave*>		SoundWaves;

	USoundWave* GetSoundWaveRandom() const;
};

UCLASS(BlueprintType, Blueprintable)
class SOUNDDESIGNERTOOLS_API USoundWaveSourceDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSoundWaveSourceGroup>		PhysicalMaterialSoundWaves;

public :
	USoundWave* GetSoundWave(int32 PhysicsAssetIndex);
};
