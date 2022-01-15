﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionComponent.h"
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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UComponentMovementComponent : public UActionComponent
{
	GENERATED_BODY()
	
public :
	UComponentMovementComponent();

protected :
	//변화에 대한 Delta 값입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	float	InterpSpeed = 1.f;

	//Delta Transform을 정의합니다. Delta값입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	FTransform	DestinationDeltaTransform;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	EActionComponentToType	ActionComponentToType = EActionComponentToType::Parent;

	//이름의 Type을 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	ENameType				NameType;

	//Move Action을 수행할 Component의 이름일 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent", meta = (EditCondition = "ActionComponentToType == EActionComponentToType::ComponentName", EditConditionHides))
	FName					ActionName;

	//Delta Transform에서 Location의 적용유무를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	bool	bIsUpdateLocation = true;

	//Delta Transform에서 Rotator의 적용유무를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	bool	bIsUpdateRotator = false;

	//Delta Transform에서 Scale의 적용유무를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	bool	bIsUpdateScale = true;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Debug|ComponentMovementComponent")
	TArray<FComponentMovementData>	ComponentMovementDatas;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
