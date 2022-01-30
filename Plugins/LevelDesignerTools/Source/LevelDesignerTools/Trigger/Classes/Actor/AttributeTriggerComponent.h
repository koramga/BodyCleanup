// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "AttributeTriggerComponent.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class ELevelAttributeTriggerActionType : uint8
{
	Visible,
	InVisible,
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelAttributeTriggerAction
{
	GENERATED_BODY()

public:
	ELevelAttributeTriggerActionType	ActionType;
	int32								TriggerIndex;
	bool								bIsTag;
	TArray<FName>						Names;
};

UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UAttributeTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public:
	UAttributeTriggerComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeTriggerComponent")
	TArray<FLevelAttributeTriggerAction>	LevelAttributeTriggerActions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32	MaxTriggerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32	CurrentTriggerIndex = 0;

protected :
	virtual void ExecuteTriggerAction(const FLevelAttributeTriggerAction& ExecuteAction);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
