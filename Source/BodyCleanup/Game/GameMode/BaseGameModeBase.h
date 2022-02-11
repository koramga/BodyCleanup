// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/GameMode/LevelToolsGameModeBase.h"
#include "LevelDesignerTools/Trigger/Managers/LevelTriggerManager.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode/SoundToolsGameModeBaseInterface.h"
#include "Manager/SoundToolsManager.h"
#include "BaseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseGameModeBase : public AGameModeBase, public ILevelToolsGameModeBase, public ISoundToolsGameModeBaseInterface
{
	GENERATED_BODY()

protected :
	UPROPERTY()
	ULevelTriggerManager*	LevelTriggerManager;

	UPROPERTY()
	USoundToolsManager*		SoundToolsManager;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UBaseScreenWidget>	BaseScreenWidgetClass;

	class UBaseScreenWidget*	BaseScreenWidget;

public :
	ABaseGameModeBase();

protected :
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void RegisterTrigger(class ILevelTriggerInterface* LevelTriggerInterface) override;
	virtual void UnRegisterTrigger(class ILevelTriggerInterface* LevelTriggerInterface) override;
	virtual const ULevelTriggerManager* GetLevelTriggerManager() const override;
	virtual void UpdateTrigger(class ILevelTriggerInterface* LevelTriggerInterface, bool bInputIsOnTrigger) override;
	virtual void UpdateTriggerOnce(class ILevelTriggerInterface* LevelTriggerInterface) override;

public :
	TSoftObjectPtr<UBaseScreenWidget> GetBaseScreenWidget() const;
	virtual TSoftObjectPtr<class USoundToolsManager> GetSoundToolsManager() override;
	void SetFocusOnCharacter(bool bIsFocusOnTheCharacter);
	bool IsFocusOnCharacter() const;
};
