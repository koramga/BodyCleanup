// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundToolsManager.h"


bool USoundToolsManager::AddAudioComponent(const FName& InName, class UAudioComponent* InAudioComponent, float InFadeOutTime)
{
	FSoundToolItemList* SoundToolItemList = SoundToolItemLists.Find(InName);

	if (nullptr == SoundToolItemList)
	{
		SoundToolItemLists.Add(InName, FSoundToolItemList());
		SoundToolItemList = SoundToolItemLists.Find(InName);
	}

	if (nullptr != SoundToolItemList)
	{
		FSoundToolItem NewSoundToolItem;

		NewSoundToolItem.AudioComponent = InAudioComponent;
		NewSoundToolItem.Name = InName;
		NewSoundToolItem.FadeOutTime = InFadeOutTime;

		SoundToolItemList->SoundToolItemList.Add(NewSoundToolItem);
	}

	return true;
}

bool USoundToolsManager::RemoveAudioComponents(const FName& InName)
{
	return true;
}