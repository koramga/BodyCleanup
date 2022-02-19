// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCorpseGameSetComponent.h"

#include "BodyCleanup/Game/GameMode/MainGameModeBase.h"

URobotCorpseGameSetComponent::URobotCorpseGameSetComponent()
{
	
}

void URobotCorpseGameSetComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if(InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		//여기서 부터 진행합니다.
		//우선 Robot Corpse가 적용되어야합니다.
		AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());

		MainGameModeBase->SetRobotCorpse(RobotCorpseActors);		
	}
}
