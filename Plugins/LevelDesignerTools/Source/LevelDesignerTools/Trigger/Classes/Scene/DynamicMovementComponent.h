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
	//변화에 대한 Delta 값입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	float	InterpSpeed = 1.f;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|LevelTriggerInputTo")
	FLevelTriggerInputTo	LevelTriggerInputTo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	TArray<FTransform>		DestinationDeltaTransforms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	EDynamicMovementCycleType DynamicMovementCycleType;

	//Delta Transform에서 Location의 적용유무를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	bool	bIsUpdateLocation = true;

	//Delta Transform에서 Rotator의 적용유무를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	bool	bIsUpdateRotator = false;

	//Delta Transform에서 Scale의 적용유무를 결정합니다.
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