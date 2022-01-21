// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelTriggerInterface.generated.h"

UENUM(BlueprintType)
enum class ELevelTriggerReactType : uint8
{
	//한 번의 Trigger에만 반응합니다.
	Once,
	//여러 번의 Trigger에 반응합니다.
	Again,
};

UENUM(BlueprintType)
enum class ELevelTriggerInputNodeType : uint8
{
	//부모 Component로부터 Trigger가 설정됩니다.
	Parent,
	//사용자가 설정한 Setup에 맞게 Trigger가 설정됩니다.
	Setup,
	//사용자가 설정할 수 없습니다. 만약 사용자가 강제로 설정한다면 Trigger가 동작되지 않습니다.
	Action UMETA(Hidden),
};

UENUM(BlueprintType)
enum class ELevelTriggerActionType : uint8
{
	//부모 Component를 Action 합니다.
	Parent,
	//Component Setup으로 부터 결정됩니다.
	Setup,
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelTriggerInputNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<AActor>							Actor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool											bIsTag = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName>									Names;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelTriggerInput
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELevelTriggerInputNodeType		LevelTriggerInputNodeType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELevelTriggerReactType			LevelTriggerReactType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FLevelTriggerInputNode>	LevelTriggerInputNodes;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelTriggerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEVELDESIGNERTOOLS_API ILevelTriggerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) = 0;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) = 0;
	virtual const FLevelTriggerInput* GetLevelTriggerInput() const = 0;
};
