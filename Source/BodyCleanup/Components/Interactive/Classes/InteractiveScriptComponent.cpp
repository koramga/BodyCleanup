// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveScriptComponent.h"
#include "../../../Game/GameInstance/BaseGameInstance.h"
#include "../../../Game/GameMode/MainGameModeBase.h"
#include "../../../Data/TableRow/TableRows.h"

UInteractiveScriptComponent::UInteractiveScriptComponent()
{
	
}

void UInteractiveScriptComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInteractiveScriptComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		//여기서부터 시작합니다.
		//일단 여기가 제대로 들어오는지 봅시다.

		AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());

		if(IsValid(MainGameModeBase))
		{
			UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(MainGameModeBase->GetGameInstance());

			if(IsValid(BaseGameInstance))
			{
				TArray<FScriptTableRow> ScriptTableRows;
				
				BaseGameInstance->GetScripts(ScriptTableRows, SceneName);

				//Script는 받아진다. 이 상태에서 이제 시작된다. 모든 포커스는 여기로 잡힐거기때문에 
			}
		}
	}
}
