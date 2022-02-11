// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_SoundTool.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "SoundTool/SoundWaveToolDataAsset.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode/SoundToolsGameModeBaseInterface.h"
#include "SoundTool/SoundWaveSourceDataAsset.h"
#include "Manager/SoundToolsManager.h"

int32 UAnimNotify_SoundTool::GetPhysicalMaterialIndex() const
{
	return 0;
}

FString UAnimNotify_SoundTool::GetNotifyName_Implementation() const
{
	return TEXT("SoundTool");
}

void UAnimNotify_SoundTool::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	int32 PhysicalMaterialIndex = GetPhysicalMaterialIndex();
	AGameModeBase* GameModeBase = MeshComp->GetWorld()->GetAuthGameMode();
	TSoftObjectPtr<USoundToolsManager> SoundToolsManager;
	
	if(IsValid(GameModeBase))
	{
		if (GameModeBase->GetClass()->ImplementsInterface(USoundToolsGameModeBaseInterface::StaticClass()))
		{
			SoundToolsManager = Cast<ISoundToolsGameModeBaseInterface>(GameModeBase)->GetSoundToolsManager();
		}		
	}
	
	for (USoundToolDataAsset* SoundToolDataAsset : SoundToolDataAssets)
	{
		if (IsValid(SoundToolDataAsset))
		{
			UAudioComponent* AudioComponent = nullptr;

			if (SoundToolDataAsset->IsA(USoundWaveToolDataAsset::StaticClass()))
			{
				USoundWaveToolDataAsset* SoundWaveToolDataAsset = Cast<USoundWaveToolDataAsset>(SoundToolDataAsset);

				if (IsValid(SoundWaveToolDataAsset))
				{
					const TArray<FSoundWave2DInfo>& Sound2DWaveInfos = SoundWaveToolDataAsset->GetSoundWave2DInfos();

					for (const FSoundWave2DInfo& SoundWave2DInfo : Sound2DWaveInfos)
					{
						if (SoundWave2DInfo.bIsIgnoreWhenContaintsName)
						{
							if (SoundToolsManager.IsValid()
								&& SoundToolsManager->IsContainsName(SoundWave2DInfo.Name))
							{
								continue;
							}
						}

						USoundWave* SoundWave = SoundWave2DInfo.SoundWaveSourceDataAsset->GetSoundWave(PhysicalMaterialIndex);

						if(false == IsValid(SoundWave))
						{
							continue;
						}

						AudioComponent = UGameplayStatics::SpawnSound2D(this, SoundWave, SoundWave2DInfo.VolumeMultiplier, SoundWave2DInfo.PitchMultiplier, SoundWave2DInfo.StartTimer, SoundWave2DInfo.SoundConcurrency);

						if (IsValid(AudioComponent))
						{
							if (SoundWave2DInfo.FadeInTime > 0.f)
							{
								AudioComponent->FadeIn(SoundWave2DInfo.FadeInTime, 1.f, 0.f, EAudioFaderCurve::Linear);
							}

							if(SoundToolsManager.IsValid())
							{
								if (false == SoundWave2DInfo.bIsAvailableDuplicated)
								{
									SoundToolsManager->RemoveAudioComponents(SoundWave2DInfo.Name);
								}

								SoundToolsManager->AddAudioComponent(SoundWave2DInfo.Name, AudioComponent, SoundWave2DInfo.FadeOutTime);								
							}
						}
					}

					const TArray<FSoundWave3DInfo>& Sound3DWaveInfos = SoundWaveToolDataAsset->GetSoundWave3DInfos();

					for (const FSoundWave3DInfo& SoundWave3DInfo : Sound3DWaveInfos)
					{
						if (SoundWave3DInfo.bIsIgnoreWhenContaintsName)
						{
							if (SoundToolsManager.IsValid()
								&& SoundToolsManager->IsContainsName(SoundWave3DInfo.Name))
							{
								continue;
							}
						}

						USoundWave* SoundWave = SoundWave3DInfo.SoundWaveSourceDataAsset->GetSoundWave(PhysicalMaterialIndex);

						if(false == IsValid(SoundWave))
						{
							continue;
						}

						if (false == SoundWave3DInfo.bIsAttachSound)
						{
							FTransform ComponentTranform = MeshComp->GetComponentTransform();
							
							AudioComponent = UGameplayStatics::SpawnSoundAtLocation(MeshComp->GetWorld(), SoundWave, ComponentTranform.GetLocation(), ComponentTranform.GetRotation().Rotator(), SoundWave3DInfo.VolumeMultiplier, SoundWave3DInfo.PitchMultiplier, SoundWave3DInfo.StartTimer, SoundWave3DInfo.SoundAttenuation, SoundWave3DInfo.SoundConcurrency);
						}
						else
						{
							AudioComponent = UGameplayStatics::SpawnSoundAttached(SoundWave, MeshComp,  SoundWave3DInfo.AttachName, SoundWave3DInfo.Location, SoundWave3DInfo.AttachLocationType, SoundWave3DInfo.bIsStopWhenAttachedToDestroyed, SoundWave3DInfo.VolumeMultiplier, SoundWave3DInfo.PitchMultiplier, SoundWave3DInfo.StartTimer, SoundWave3DInfo.SoundAttenuation, SoundWave3DInfo.SoundConcurrency, true);
						}

						if (IsValid(AudioComponent))
						{
							if (SoundWave3DInfo.FadeInTime > 0.f)
							{
								AudioComponent->FadeIn(SoundWave3DInfo.FadeInTime, 1.f, 0.f, EAudioFaderCurve::Linear);
							}

							if(SoundToolsManager.IsValid())
							{
								if (false == SoundWave3DInfo.bIsAvailableDuplicated)
								{
									SoundToolsManager->RemoveAudioComponents(SoundWave3DInfo.Name);
								}

								SoundToolsManager->AddAudioComponent(SoundWave3DInfo.Name, AudioComponent, SoundWave3DInfo.FadeOutTime);								
							}
						}
					}

					if(SoundToolsManager.IsValid())
					{
						const TArray<FName>& DataAssetSoundWaveTurnOffNames = SoundWaveToolDataAsset->GetSoundWaveTurnOffNames();

						for (const FName& Name : DataAssetSoundWaveTurnOffNames)
						{
							SoundToolsManager->RemoveAudioComponents(Name);
						}
					}
				}
			}
		}
	}
	
	if(SoundToolsManager.IsValid())
	{
		for(const FName& Name : SoundWaveTurnOffNames)
		{
			SoundToolsManager->RemoveAudioComponents(Name);
		}
	}
}
