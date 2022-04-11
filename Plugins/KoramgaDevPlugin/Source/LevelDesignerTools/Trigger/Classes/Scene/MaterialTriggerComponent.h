// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerSceneComponent.h"
#include "MetaTools/Variable/BaseVariableMetaData.h"
#include "MetaTools/VariableGroup/MaterialInstanceVariable.h"
#include "MaterialTriggerComponent.generated.h"

/**
 * 
*/
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UMaterialTriggerComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()

public :
	UMaterialTriggerComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

public :
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TArray<TSoftObjectPtr<UPrimitiveComponent>>			PrimitiveComponents;
	
	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	FLevelTriggerInputTo				LevelTriggerInputTo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float								MaterialUpdateKeepTime = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMaterialInstanceVariable>	MaterialInstanceVariables;

	TArray<TMetaVariable>				BackupMetaVariables;
	float								MaterialTickTime = -1.f;
};
