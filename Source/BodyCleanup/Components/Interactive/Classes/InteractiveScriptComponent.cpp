// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveScriptComponent.h"

void UInteractiveScriptComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInteractiveScriptComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		//레벨에 대한 정보가 필요하다.
		//TMap..
	}
}
