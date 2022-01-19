// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Interfaces/LevelTriggerInterface.h"
#include "UObject/NoExportTypes.h"
#include "LevelTriggerManager.generated.h"

/**
 * 
 */


struct FLevelTriggerCertificate
{
	TSoftObjectPtr<UObject>				OverlappedComp;
	TArray<TSoftObjectPtr<UObject>>		OtherComps;

	FLevelTriggerCertificate()
		:OverlappedComp(nullptr) {}

	FLevelTriggerCertificate(const TSoftObjectPtr<UObject>& _OverlappedComp)
		: OverlappedComp(_OverlappedComp) {}
};

class LEVELDESIGNERTOOLS_API CLevelTriggerInterfaceSpace
{
public :
	CLevelTriggerInterfaceSpace(const TSoftObjectPtr<ILevelTriggerInterface>& InputLevelTriggerInterface);
	~CLevelTriggerInterfaceSpace();

private :
	TSoftObjectPtr<ILevelTriggerInterface>						LevelTriggerInterface;
	TArray<TSoftObjectPtr<UObject>>								TriggerComponents;
	TMap<TSoftObjectPtr<UObject>, FLevelTriggerCertificate>		TriggerCertificateComponents;
	TArray<TSoftObjectPtr<ILevelTriggerInterface>>				ObserverTriggerLevelInterfaces;

public :
	void SetTriggerComponents(TArray<TSoftObjectPtr<UObject>>& InputTriggerComponents);
};


UCLASS()
class LEVELDESIGNERTOOLS_API ULevelTriggerManager : public UObject
{
	GENERATED_BODY()

protected :
	TMap<TSoftObjectPtr<ILevelTriggerInterface>, TUniquePtr<CLevelTriggerInterfaceSpace>>	LevelTriggerInterfaces;

public :
	void AddTriggerInterface(const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface);
};
