// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerSceneComponent.h"
#include "ComponentMovementComponent.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FComponentMovementData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<USceneComponent>	MovementComponent;

	UPROPERTY(VisibleAnywhere)
	FTransform						SourceTransform;

	UPROPERTY(VisibleAnywhere)
	FTransform						DestinationTransform;

	FComponentMovementData()
		: MovementComponent(nullptr) {}

	FComponentMovementData(TSoftObjectPtr<USceneComponent> _MovementComponent)
		: MovementComponent(_MovementComponent) 
	{
		if (MovementComponent.IsValid())
		{
			SourceTransform = MovementComponent->GetRelativeTransform();
		}
	}
};

UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UComponentMovementComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()
	
public :
	UComponentMovementComponent();

protected :
	//1초 뒤에 결과가 도착할 예정이므로 배속을 결정합니다. (값이 0.5이면 도착까지 걸리는 시간이 2초가 된다는 의미입니다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	float	InterpSpeed = 1.f;

	//Delta Transform을 정의합니다. Delta값입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	FTransform	DestinationDeltaTransform;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	FLevelTriggerInputTo	LevelTriggerInputTo;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Debug|ComponentMovementComponent")
	TArray<FComponentMovementData>	ComponentMovementDatas;

	UPROPERTY(VisibleAnywhere, Category = "Debug|DynamicMovementComponent")
	float							TriggerDeltaTime;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
