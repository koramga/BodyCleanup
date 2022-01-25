// Fill out your copyright notice in the Description page of Project Settings.


#include "KillTriggerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"

UKillTriggerComponent::UKillTriggerComponent()
{
	LevelTriggerInputFrom.LevelTriggerInputNodeFromType = ELevelTriggerInputNodeFromType::Setup;
}

void UKillTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKillTriggerComponent::SetupTrigger()
{
}

void UKillTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		AActor* Owner = GetOwner();

		if (IsValid(Owner))
		{
			if (Owner->GetLifeSpan() <= 0.f)
			{
				float KillTimer = KillTime.GetMetaVariable().Get<float>();

				if (KillTimer > 0.f)
				{
					Owner->SetLifeSpan(KillTimer);
				}
				else
				{
					Owner->Destroy();
				}
			}
		}
	}
}
