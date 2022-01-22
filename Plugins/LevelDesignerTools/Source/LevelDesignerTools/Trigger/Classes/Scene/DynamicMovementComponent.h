// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerSceneComponent.h"
#include "DynamicMovementComponent.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FDynamicMovementParam
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<USceneComponent>	MovementComponent;

	UPROPERTY(VisibleAnywhere)
	TArray<FTransform>				Transforms;

	FDynamicMovementParam()
		: MovementComponent(nullptr) {}

	FDynamicMovementParam(TSoftObjectPtr<USceneComponent> _MovementComponent)
		: MovementComponent(_MovementComponent)
	{
		Transforms.Add(MovementComponent->GetRelativeTransform());
	}
};

UENUM(BlueprintType)
enum class EDynamicMovementCycleType : uint8
{
	Cycle,
	Reverse,
};

UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UDynamicMovementComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()

public :
	UDynamicMovementComponent();

protected :
	//��ȭ�� ���� Delta ���Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	float	InterpSpeed = 1.f;

	//Action�� ������ �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|LevelTriggerInputTo")
	FLevelTriggerInputTo	LevelTriggerInputTo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	TArray<FTransform>		DestinationDeltaTransforms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	EDynamicMovementCycleType DynamicMovementCycleType;

	//Delta Transform���� Location�� ���������� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	bool	bIsUpdateLocation = true;

	//Delta Transform���� Rotator�� ���������� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	bool	bIsUpdateRotator = false;

	//Delta Transform���� Scale�� ���������� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	bool	bIsUpdateScale = true;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	TArray<FDynamicMovementParam>	DynamicMovementParams;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	int32							ComponentMovementIndex = 0;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	int32							ReverseSign = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};