// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/GameMode/LevelToolsGameModeBase.h"
#include "LevelDesignerTools/Trigger/Managers/LevelTriggerManager.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseGameModeBase : public AGameModeBase, public ILevelToolsGameModeBase
{
	GENERATED_BODY()

protected :
	UPROPERTY()
	ULevelTriggerManager* LevelTriggerManager;

public :
	ABaseGameModeBase();

protected :
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;

protected:
	virtual void InitTrigger() override;

public:
	virtual void RegisterTrigger(class ILevelTriggerInterface* LevelTriggerInterface) override;
	virtual void UnRegisterTrigger(class ILevelTriggerInterface* LevelTriggerInterface) override;
	virtual const ULevelTriggerManager* GetLevelTriggerManager() const override;
	virtual void UpdateTrigger(class ILevelTriggerInterface* LevelTriggerInterface, bool bInputIsOnTrigger) override;
	virtual void UpdateTriggerOnce(class ILevelTriggerInterface* LevelTriggerInterface) override;
	virtual void SetupTriggerAfterSpawn(AActor* Actor);
};
