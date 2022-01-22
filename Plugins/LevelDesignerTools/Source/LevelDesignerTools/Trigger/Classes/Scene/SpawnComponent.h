// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerSceneComponent.h"
#include "SpawnComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ESpawnComponentType : uint8
{
	Hidden,
	Spawn,
};

USTRUCT(BlueprintType, Blueprintable)
struct FSpawnMarkupParam
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor>								ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESpawnActorCollisionHandlingMethod				SpawnMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<AActor>							Actor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool											bIsTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName>									Names;
};

USTRUCT(BlueprintType, Blueprintable)
struct FHiddenParam
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<AActor>							Actor;

	UPROPERTY()
	FTransform										Transform;
};

UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API USpawnComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|SpawnComponent")
	ESpawnComponentType	SpawnComponentType = ESpawnComponentType::Hidden;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|SpawnComponent", meta = (EditCondition = "SpawnComponentType == ESpawnComponentType::Hidden", EditConditionHides))
	TArray<FHiddenParam>		HiddenParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|SpawnComponent", meta = (EditCondition = "SpawnComponentType == ESpawnComponentType::Spawn", EditConditionHides))
	TArray<FSpawnMarkupParam>	 SpawnMarkupParams;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;

private :
	void GetTransformsFromSpawnMarkupParam(TArray<FTransform>& Transforms, const FSpawnMarkupParam& SpawnMarkupParam);
	void GetActorsFromSpawnMarkupParam(TArray<TSoftObjectPtr<UObject>>& Objects, const FSpawnMarkupParam& SpawnMarkupParam);
	
public :
	void GetAffectPoints(TArray<FVector>& Locations);
};
