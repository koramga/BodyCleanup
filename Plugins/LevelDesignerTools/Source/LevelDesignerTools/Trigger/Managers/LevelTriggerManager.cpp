// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerManager.h"

CLevelTriggerInterfaceSpace::CLevelTriggerInterfaceSpace(const TSoftObjectPtr<ILevelTriggerInterface>& InputLevelTriggerInterface)
{
	LevelTriggerInterface = InputLevelTriggerInterface;
}

CLevelTriggerInterfaceSpace::~CLevelTriggerInterfaceSpace()
{
}

void CLevelTriggerInterfaceSpace::SetTriggerComponents(TArray<TSoftObjectPtr<UObject>>& InputTriggerComponents)
{
	for (const TSoftObjectPtr<UObject>& InputTriggerComponent : InputTriggerComponents)
	{
		TriggerComponents.Add(InputTriggerComponent);
	}
}

void ULevelTriggerManager::AddTriggerInterface(const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface)
{
	TUniquePtr<CLevelTriggerInterfaceSpace>* LevelTriggerInterfaceSpace = LevelTriggerInterfaces.Find(TriggerInterface);

	if (nullptr == LevelTriggerInterfaceSpace)
	{
		LevelTriggerInterfaces.Add(TriggerInterface, TUniquePtr<CLevelTriggerInterfaceSpace>(new CLevelTriggerInterfaceSpace(TriggerInterface)));
	}
}
