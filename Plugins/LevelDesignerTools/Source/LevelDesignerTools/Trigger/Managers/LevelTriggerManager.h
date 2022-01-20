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
	TSoftObjectPtr<UObject>							OverlappedComp;
	TArray<TSoftObjectPtr<UPrimitiveComponent>>		OtherComps;

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
	TSoftObjectPtr<ULevelTriggerManager>						LevelTriggerManager;
	UPROPERTY()
	TSoftObjectPtr<ILevelTriggerInterface>						LevelTriggerInterface;
	UPROPERTY()
	TArray<TSoftObjectPtr<UActorComponent>>						TriggerComponents;
	UPROPERTY()
	TMap<TSoftObjectPtr<UObject>, FLevelTriggerCertificate>		TriggerCertificateComponents;
	UPROPERTY()
	TArray<TSoftObjectPtr<ULevelTriggerInterfaceSpace>>			ObserverTriggerLevelInterfaceSpaces;

	bool														bIsOnTrigger = false;


private:
	UFUNCTION()
	void __OnTriggerComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void __OnTriggerComponentOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private :
	void __ProcessTrigger(bool bInputIsOnTrigger);
	void __CalledTriggerObservers(TSoftObjectPtr<USceneComponent> CallerActorComponent, bool bIsInputOnTrigger);
	void __CallTriggerObservers(bool bIsInputOnTrigger);
	void __AddTriggerObserver(const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace);

public :
	void Initialize();
	void UpdateTrigger(bool bInputIsOnTrigger);

public :
	void SetLevelTriggerInterface(const TSoftObjectPtr<ILevelTriggerInterface>& LevelTriggerInterface);
	void SetLevelTriggerManager(const TSoftObjectPtr<ULevelTriggerManager>& InputLevelTriggerManager);
	void FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace);
};


UCLASS()
class LEVELDESIGNERTOOLS_API ULevelTriggerManager : public UObject
{
	GENERATED_BODY()

protected :
	UPROPERTY()
	TMap<TSoftObjectPtr<ILevelTriggerInterface>, ULevelTriggerInterfaceSpace*>	LevelTriggerInterfaces;

public :
	ULevelTriggerInterfaceSpace* GetLevelTriggerInterfaceSpace(TSoftObjectPtr<ILevelTriggerInterface> TriggerInterface);
	void InitializeTriggerInterfaceSpace(const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface);
	void FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface);
};
