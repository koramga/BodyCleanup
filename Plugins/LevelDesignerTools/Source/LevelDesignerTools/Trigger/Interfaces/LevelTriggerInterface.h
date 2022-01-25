// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelTriggerInterface.generated.h"

#define DEFAULT_TRIGGER_INDEX	0
#define MAX_TRIGGER_NUM			32

UENUM(BlueprintType)
enum class ELevelTriggerReactType : uint8
{
	//한 번의 Trigger에만 반응합니다.
	Once,
	//여러 번의 Trigger에 반응합니다.
	Again,
};

UENUM(BlueprintType)
enum class ELevelTriggerWayType : uint8
{
	//내부에서 반응이 들어오면 Observer에게 Call을 호출한다. (Normal Trigger)
	OneWay,
	//외부에서 반응이 들어오면 Observer에게 Call을 호출한다. (ex) Time, Destroy etc)
	TwoWay,
};

UENUM(BlueprintType)
enum class ELevelTriggerInputNodeFromType : uint8
{
	//부모 Component로부터 Trigger가 설정됩니다.
	Parent,
	//사용자가 설정한 Setup에 맞게 Trigger가 설정됩니다.
	Setup,
	//사용자가 설정할 수 없습니다. 만약 사용자가 강제로 설정한다면 Trigger가 동작되지 않습니다.
	Action UMETA(Hidden),
	//아무런 Trigger도 설정되지 않습니다. Spawn시, Trigger가 바로 동작합니다.
	None,
};

UENUM(BlueprintType)
enum class ELevelTriggerInputNodeToType : uint8
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
struct FLevelTriggerInputFrom
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "LevelTriggerInputNodeFromType != ELevelTriggerInputNodeFromType::Action", EditConditionHides))
	ELevelTriggerInputNodeFromType		LevelTriggerInputNodeFromType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "LevelTriggerInputNodeFromType == ELevelTriggerInputNodeFromType::Parent || LevelTriggerInputNodeFromType == ELevelTriggerInputNodeFromType::Setup", EditConditionHides))
	ELevelTriggerReactType				LevelTriggerReactType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "LevelTriggerInputNodeFromType == ELevelTriggerInputNodeFromType::Setup", EditConditionHides))
	TArray<FLevelTriggerInputNode>		LevelTriggerInputNodes;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelTriggerInputTo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELevelTriggerInputNodeToType		LevelTriggerInputNodeToType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "LevelTriggerInputNodeToType == ELevelTriggerInputNodeToType::Setup", EditConditionHides))
	TArray<FLevelTriggerInputNode>		LevelTriggerInputNodes;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelTriggerUpdateParam
{
	GENERATED_BODY()

public:
	bool					bIsOnTrigger;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelTriggerUpdateActionParam
{
	GENERATED_BODY()

public:
	bool					bIsOnTrigger;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelTriggerSettings
{
	GENERATED_BODY()

public:
	ELevelTriggerWayType	LevelTriggerWayType;
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
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& LevelTriggerUpdateParam) = 0;
	virtual void UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam) = 0;
	virtual const FLevelTriggerInputFrom* GetLevelTriggerInputFrom() const = 0;
	virtual void SetupTrigger() = 0;
	virtual bool IsOnTrigger() const = 0;
	virtual const FLevelTriggerSettings& GetLevelTriggerSettings() const = 0;
};
