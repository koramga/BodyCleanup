﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "Components/SceneComponent.h"
#include "Interfaces/LevelTriggerInterface.h"
#include "TriggerComponent.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FTriggerActorWithName
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<AActor>							Actor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ENameType										NameType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName>									Names;
};

USTRUCT(BlueprintType, Blueprintable)
struct FTriggerOnData
{
	GENERATED_BODY()

public:
	TSoftObjectPtr<UActorComponent>	OverlappedComp;
	TArray<TSoftObjectPtr<UPrimitiveComponent>>	OtherComps;

	FTriggerOnData()
		:OverlappedComp(nullptr) {}

	FTriggerOnData(TSoftObjectPtr<UActorComponent> _OverlappedComp)
		: OverlappedComp(_OverlappedComp) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UTriggerComponent: public USceneComponent, public ILevelTriggerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerComponent();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool										bIsCanControlTriggerComponentFromType;

	//Trigger Action을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TriggerComponent", meta = (EditCondition = "bIsCanControlTriggerComponentFromType == true"))
	ETriggerComponentFromType					TriggerComponentFromType = ETriggerComponentFromType::Parent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TriggerComponent", meta = (EditCondition = "TriggerComponentFromType == ETriggerComponentFromType::Setup", EditConditionHides))
	TArray<FTriggerActorWithName>				TriggerActorWithNames;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Debug|TriggerComponent")
	TArray<TSoftObjectPtr<USceneComponent>>					TriggerComponents;

	//발생 증거가 되는 Component를 Key로 둔다.
	UPROPERTY(VisibleAnywhere, Category = "Debug|TriggerComponent")
	TMap<TSoftObjectPtr<USceneComponent>, FTriggerOnData>		TriggerOnComponents;

	UPROPERTY(VisibleAnywhere, Category = "Debug|TriggerComponent")
	TArray<TSoftObjectPtr<ILevelTriggerInterface>>			ObserverTriggerLevelInterfaces;

	UPROPERTY(VisibleAnywhere, Category = "Debug|TriggerComponent")
	bool													bIsOnTrigger = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void __OnTriggerComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void __OnTriggerComponentOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private :
	void __GetTriggerComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents);
	void __ProcessTrigger(bool bInputIsOnTrigger);
	void __FindTriggerOnActors(TArray<TSoftObjectPtr<AActor>>& Actors, const TSoftObjectPtr<UTriggerComponent> TriggerComponent);
	void __AddTriggerComponents(TArray<TSoftObjectPtr<USceneComponent>>& DestTriggerComponents, const TArray<TSoftObjectPtr<USceneComponent>>& PushComponents);

protected:
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) override;
	virtual void CallTriggerObservers(bool bIsInputOnTrigger) override;
	virtual void AddTriggerObserver(TSoftObjectPtr<ILevelTriggerInterface> LevelTriggerInterface) override;
	virtual void CalledTriggerObservers(TSoftObjectPtr<USceneComponent> CallerActorComponent, bool bIsInputOnTrigger) override;

protected :
	virtual void UpdateTrigger(bool bInputIsOnTrigger);
	void FindTriggerOnActors(TArray<TSoftObjectPtr<AActor>>& Actors);

public:
	virtual bool IsOnTrigger() const override;
};
