// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveTriggerComponent.h"
#include "InteractiveScriptComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EScriptActorInputType : uint8
{
	Actor,
	Name,
};

USTRUCT(BlueprintType)
struct FActorDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EScriptActorInputType	ScriptActorInputType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ScriptActorInputType == EScriptActorInputType::Actor", EditConditionHides))
	TSoftObjectPtr<AActor>	Actor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ScriptActorInputType == EScriptActorInputType::Name", EditConditionHides))
	FName					Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					CameraName;
};

struct FScriptTableRowToMainScript
{
	TSoftObjectPtr<AActor>	Actor;
	TSoftObjectPtr<class UCameraComponent>	CameraComponent;
	
};

UCLASS(ClassGroup = (Interactive), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UInteractiveScriptComponent : public UInteractiveTriggerComponent
{
	GENERATED_BODY()

public :
	UInteractiveScriptComponent();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName						SceneName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FActorDescription>	ActorDescriptions;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
