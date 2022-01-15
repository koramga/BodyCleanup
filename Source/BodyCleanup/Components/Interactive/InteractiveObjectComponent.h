// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../InteractiveComponent.h"
#include "InteractiveObjectComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UInteractiveObjectComponent : public UInteractiveComponent
{
	GENERATED_BODY()

public :
	UInteractiveObjectComponent();
	
protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInteractiveObjectType	InteractiveObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					AbsorbingInterpValue;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent")
	EActionComponentToType		ActionComponentToType = EActionComponentToType::Parent;

	//이름의 Type을 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent", meta = (EditCondition = "ActionComponentToType == EActionComponentToType::Setup", EditConditionHides))
	ENameType				NameType;

	//Move Action을 수행할 Component의 이름일 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|DynamicMovementComponent", meta = (EditCondition = "ActionComponentToType == EActionComponentToType::Setup", EditConditionHides))
	FName					ActionName;

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform							InteractiveTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UPrimitiveComponent>>	InteractivePrimitiveComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void UpdateInteractiveAction(EInteractiveAction NextInteractiveAction, EInteractiveAction BeforeInteractiveAction) override;

public :
	EInteractiveObjectType	GetInteractiveObjectType()	const;
};
