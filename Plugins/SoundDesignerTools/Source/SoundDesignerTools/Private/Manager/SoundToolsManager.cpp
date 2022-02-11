// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundToolsManager.h"
#include "Components/AudioComponent.h"


bool USoundToolsManager::AddAudioComponent(const FName& InName, class UAudioComponent* InAudioComponent, float InFadeOutTime)
{
	if (InName.IsNone())
	{
		return false;
	}

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

		return true;
	}

	return false;
}

bool USoundToolsManager::IsContainsName(const FName& InName)
{
	if (InName.IsNone())
	{
		return false;
	}

	FSoundToolItemList* SoundToolItemList = SoundToolItemLists.Find(InName);

	if(nullptr == SoundToolItemList)
	{
		return false;
	}

	bool bIsContained = false;

	for (FSoundToolItem& SoundToolItem : SoundToolItemList->SoundToolItemList)
	{
		if(IsValid(SoundToolItem.AudioComponent))
		{
			return true;
		}
	}

	SoundToolItemLists.Remove(InName);

	return false;
}

bool USoundToolsManager::RemoveAudioComponents(const FName& InName)
{
	if (InName.IsNone())
	{
		return false;
	}

	FSoundToolItemList* SoundToolItemList = SoundToolItemLists.Find(InName);

	if (nullptr != SoundToolItemList)
	{
		for (FSoundToolItem& SoundToolItem : SoundToolItemList->SoundToolItemList)
		{
			if (IsValid(SoundToolItem.AudioComponent))
			{
				SoundToolItem.AudioComponent->FadeOut(SoundToolItem.FadeOutTime, 0.f, EAudioFaderCurve::Linear);
			}
		}

		SoundToolItemLists.Remove(InName);

		return true;
	}

	return false;
}

void USoundToolsManager::ClearAudioComponents()
{
	for (auto Lists : SoundToolItemLists)
	{
		for (FSoundToolItem& SoundToolItem : Lists.Value.SoundToolItemList)
		{
			if (IsValid(SoundToolItem.AudioComponent))
			{
				SoundToolItem.AudioComponent->FadeOut(SoundToolItem.FadeOutTime, 0.f, EAudioFaderCurve::Linear);
			}
		}
	}

	SoundToolItemLists.Empty();
}
