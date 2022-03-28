// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound3DTriggerComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

USound3DTriggerComponent::USound3DTriggerComponent()
{
}

void USound3DTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USound3DTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void USound3DTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
	
	if(InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		if(IsValid(AudioComponent))
		{
			AudioComponent->Stop();
		}

		//기존 트리거랑 다른 방식으로 가야하나? Sound는 ??
		//계속해서 소리가 재생되는 상태에 있어야하나?? 멀리 떨어지면 제거되어야하나??
		//기존 트리거에 발븡면 계속 재ㅐㅐㅐㅐㅐㅐㅐㅐ생 아니면 Stop 이 기준으로 가는데 음...어떻게 해야하지?
		
		FTransform Transform = GetComponentToWorld();
		
		AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, SoundWave, Transform.GetLocation(), Transform.Rotator(), VolumeMultiplier, PitchMultiplier, StartTimer, SoundAttenuation, SoundConcurrency);

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
