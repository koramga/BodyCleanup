// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTool/SoundWaveToolDataAsset.h"

const TArray<FSoundWave2DInfo>& USoundWaveToolDataAsset::GetSoundWave2DInfos() const
{
	return SoundWave2DInfos;
}

const TArray<FSoundWave3DInfo>& USoundWaveToolDataAsset::GetSoundWave3DInfos() const
{
	return SoundWave3DInfos;
}

const TArray<FName>& USoundWaveToolDataAsset::GetSoundWaveTurnOffNames() const
{
	return SoundWaveTurnOffNames;
}