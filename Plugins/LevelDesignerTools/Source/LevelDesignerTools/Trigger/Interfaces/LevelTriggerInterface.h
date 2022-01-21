// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelTriggerInterface.generated.h"

UENUM(BlueprintType)
enum class ELevelTriggerReactType : uint8
{
	//�� ���� Trigger���� �����մϴ�.
	Once,
	//���� ���� Trigger�� �����մϴ�.
	Again,
};

UENUM(BlueprintType)
enum class ELevelTriggerInputNodeType : uint8
{
	//�θ� Component�κ��� Trigger�� �����˴ϴ�.
	Parent,
	//����ڰ� ������ Setup�� �°� Trigger�� �����˴ϴ�.
	Setup,
	//����ڰ� ������ �� �����ϴ�. ���� ����ڰ� ������ �����Ѵٸ� Trigger�� ���۵��� �ʽ��ϴ�.
	Action UMETA(Hidden),
};

UENUM(BlueprintType)
enum class ELevelTriggerActionType : uint8
{
	//�θ� Component�� Action �մϴ�.
	Parent,
	//Component Setup���� ���� �����˴ϴ�.
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
