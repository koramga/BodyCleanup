// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound2DTriggerComponent.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

USound2DTriggerComponent::USound2DTriggerComponent()
{
	LevelTriggerSettings.LevelTriggerWayType = ELevelTriggerWayType::OneWay;	
}

void USound2DTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USound2DTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void USound2DTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
	
	if(InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		if(IsValid(AudioComponent))
		{
			AudioComponent->Stop();
		}
		
		AudioComponent = UGameplayStatics::SpawnSound2D(this, SoundWave);

		if(FadeInTime > 0.f)
		{
			AudioComponent->FadeIn(FadeInTime, 1.f, 0.f, EAudioFaderCurve::Linear);	
		}		
	}
	else
	{
		if(IsValid(AudioComponent))
		{
			if(FadeOutTime > 0.f)
			{
				AudioComponent->FadeOut(FadeOutTime, 0.f, EAudioFaderCurve::Linear);	
			}			
		}
	}
}