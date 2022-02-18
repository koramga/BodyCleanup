// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveScriptComponent.h"

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

		
	}
}
