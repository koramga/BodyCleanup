// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/TriggerActorComponent.h"
#include "DestructibleTriggerComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ELevelTriggerDestructibleType : uint8
{
	Radial,
	Linear,
};


USTRUCT(BlueprintType, Blueprintable)
struct FLevelDestructibleTriggerTo
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool			bIsTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName>	Names;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelDestructibleImpulseDir
{
	GENERATED_BODY()

public :
};

UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UDestructibleTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UDestructibleTriggerComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DestructibleTriggerComponent")
	FLevelDestructibleTriggerTo			DestructibleInputTo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DestructibleTriggerComponent")
	ELevelTriggerDestructibleType		LevelTriggerDestructibleType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DestructibleTriggerComponent")
	float	Damage = 1000000000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DestructibleTriggerComponent")
	float	Strength = 5000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DestructibleTriggerComponent", meta = (EditCondition = "LevelTriggerDestructibleType == ELevelTriggerDestructibleType::Radial", EditConditionHides))
	float	Radius = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DestructibleTriggerComponent", meta = (EditCondition = "LevelTriggerDestructibleType == ELevelTriggerDestructibleType::Linear", EditConditionHides))
	FVector ImpulseDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<class UDestructibleComponent>>	DestructibleComponents;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
	
};
