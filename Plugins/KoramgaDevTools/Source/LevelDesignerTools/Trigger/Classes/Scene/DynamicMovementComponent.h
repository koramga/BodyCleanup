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
	//1초 뒤에 결과가 도착할 예정이므로 배속을 결정합니다. (값이 0.5이면 도착까지 걸리는 시간이 2초가 된다는 의미입니다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	float	InterpSpeed = 1.f;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	FLevelTriggerInputTo	LevelTriggerInputTo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	TArray<FTransform>		DestinationDeltaTransforms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	EDynamicMovementCycleType DynamicMovementCycleType;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	TArray<FDynamicMovementParam>	DynamicMovementParams;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	int32							ComponentMovementIndex = 0;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	int32							ReverseSign = 1;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	float							TriggerDeltaTime;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	TArray<FTransform>				SourceTransforms;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	TArray<FTransform>				DestTransforms;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};