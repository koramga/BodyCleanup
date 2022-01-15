// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionComponent.h"
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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UDynamicMovementComponent : public UActionComponent
{
	GENERATED_BODY()

public :
	UDynamicMovementComponent();

protected :
	//변화에 대한 Delta 값입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	float	InterpSpeed = 1.f;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	EActionComponentToType		ActionComponentToType = EActionComponentToType::Parent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	EDynamicMovementCycleType	DynamicMovementCycleType = EDynamicMovementCycleType::Cycle;

	//이름의 Type을 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent", meta = (EditCondition = "ActionComponentToType == EActionComponentToType::Setup", EditConditionHides))
	ENameType				NameType;

	//Move Action을 수행할 Component의 이름일 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent", meta = (EditCondition = "ActionComponentToType == EActionComponentToType::Setup", EditConditionHides))
	FName					ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	TArray<FTransform>		DestinationDeltaTransforms;

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	virtual void OnTrigger(bool bInputIsOnTrigger) override;
};