// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Interfaces/LevelTriggerInterface.h"
#include "UObject/NoExportTypes.h"
#include "LevelTriggerManager.generated.h"

/**
 * 
 */

USTRUCT()
struct FLevelTriggerCertificate
{
	GENERATED_BODY()

public :
	TSoftObjectPtr<UObject>				OverlappedComp;
	TArray<TSoftObjectPtr<UObject>>		OtherComps;

	FLevelTriggerCertificate()
		:OverlappedComp(nullptr) {}

	FLevelTriggerCertificate(const TSoftObjectPtr<UObject>& _OverlappedComp)
		: OverlappedComp(_OverlappedComp) {}
};

UCLASS()
class LEVELDESIGNERTOOLS_API ULevelTriggerInterfaceSpace
	: public UObject
{
	GENERATED_BODY()

private :
	UPROPERTY()
	TSoftObjectPtr<ILevelTriggerInterface>						LevelTriggerInterface;
	UPROPERTY()
	TArray<TSoftObjectPtr<UObject>>								TriggerComponents;
	UPROPERTY()
	TMap<TSoftObjectPtr<UObject>, FLevelTriggerCertificate>		TriggerCertificateComponents;
	UPROPERTY()
	TArray<TSoftObjectPtr<ILevelTriggerInterface>>				ObserverTriggerLevelInterfaces;

	bool														bIsOnTrigger = false;


private:
	UFUNCTION()
	void __OnTriggerComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void __OnTriggerComponentOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private :
	void __InitTrigger();
	void __ProcessTrigger(bool bInputIsOnTrigger);

public :
	void AddTriggerComponents(TSoftObjectPtr<UObject>& InputTriggerComponent);
	void SetLevelTriggerInterface(const TSoftObjectPtr<ILevelTriggerInterface>& LevelTriggerInterface);

public :
	void UpdateTrigger(bool bInputIsOnTrigger);
};


UCLASS()
class LEVELDESIGNERTOOLS_API ULevelTriggerManager : public UObject
{
	GENERATED_BODY()

protected :
	TMap<TSoftObjectPtr<ILevelTriggerInterface>, TUniquePtr<ULevelTriggerInterfaceSpace>>	LevelTriggerInterfaces;

public :
	void AddTriggerInterface(const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface);
};
