// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/GameSetTriggerComponent.h"
#include "RobotCorpseGameSetComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(GameSet), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API URobotCorpseGameSetComponent : public UGameSetTriggerComponent
{
	GENERATED_BODY()

public :
	URobotCorpseGameSetComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|RobotCorpseGameSetComponent")
	TArray<TSoftObjectPtr<class ARobotCorpseActor>>	RobotCorpseActors;		//지정해줍니다.	

protected:
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
