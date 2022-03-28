// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZoneTriggerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "LevelDesignerTools/GameMode/LevelToolsGameModeBase.h"
#include "../../../Actor/LevelToolsActorInterface.h"

UKillZoneTriggerComponent::UKillZoneTriggerComponent()
{

}

void UKillZoneTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKillZoneTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UKillZoneTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		TArray<TSoftObjectPtr<AActor>> Actors;

		if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
		{
			ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

			if (nullptr != LevelToolsGameModeBase)
			{
				const ULevelTriggerManager* LevelTriggerManager = LevelToolsGameModeBase->GetLevelTriggerManager();

				if (IsValid(LevelTriggerManager))
				{
					LevelTriggerManager->FindOverlapActors(Actors, this);
				}
			}

			for (const TSoftObjectPtr<AActor>& Actor : Actors)
			{
				bool bExcept = false;
				
				if(ExceptActors.Contains(Actor))
				{
					//Skip한다.
					bExcept = true;
				}

				if(false == bExcept)
				{
					for(TSubclassOf<AActor>& ExceptActorClass : ExceptActorClasses)
					{
						if(Actor->IsA(ExceptActorClass))
						{
							bExcept = true;
							break;
						}
					}					
				}

				if(bExcept)
				{
					continue;
				}
			
				if (Actor->GetClass()->ImplementsInterface(ULevelToolsActorInterface::StaticClass()))
				{
					Cast<ILevelToolsActorInterface>(Actor.Get())->SetDestroyFromTrigger();
				}
				else
				{
					Actor->Destroy();
				}
			}
		}
	}
}
