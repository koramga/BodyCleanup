// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTool/SoundWaveSourceDataAsset.h"

USoundWave* FSoundWaveSourceGroup::GetSoundWaveRandom() const
{
	if(SoundWaves.Num() == 0)
	{
		return nullptr;
	}
	else if(SoundWaves.Num() == 1)
	{
		return SoundWaves[0];
	}

	int32 Index = FMath::RandRange(0, SoundWaves.Num() - 1);

	return SoundWaves[Index];
}

USoundWave* USoundWaveSourceDataAsset::GetSoundWave(int32 PhysicsAssetIndex)
{
	if(PhysicalMaterialSoundWaves.Num() == 0)
	{
		return nullptr;
	}

	if(PhysicsAssetIndex >= 0
		&& PhysicsAssetIndex < PhysicalMaterialSoundWaves.Num())
	{
		const FSoundWaveSourceGroup& SoundWaveSourceGroup = PhysicalMaterialSoundWaves[PhysicsAssetIndex];

		if(SoundWaveSourceGroup.SoundWaves.Num() > 0)
		{
			return SoundWaveSourceGroup.GetSoundWaveRandom();
		}		
	}

	const FSoundWaveSourceGroup& DefaultSoundWaveSourceGroup = PhysicalMaterialSoundWaves[0];
	
	return DefaultSoundWaveSourceGroup.GetSoundWaveRandom();
}
