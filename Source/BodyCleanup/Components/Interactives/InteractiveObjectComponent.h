// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../InteractiveComponent.h"
#include "InteractiveObjectComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Interactives), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UInteractiveObjectComponent : public UInteractiveComponent
{
	GENERATED_BODY()

public :
	UInteractiveObjectComponent();
	
protected :
	//Vacuum시, 빨아들여지는 속도를 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent", meta = (EditCondition = "InteractiveType == EInteractiveType::Rigid || InteractiveType == EInteractiveType::Junk", EditConditionHides))
	float					AbsorbingSpeedPerSecond = 500.f;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent")
	EInteractiveComponentToType		InteractiveComponentToType = EInteractiveComponentToType::Parent;

	//흡수되는 정크의 양을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent", meta = (EditCondition = "InteractiveType == EInteractiveType::Junk", EditConditionHides))
	int32					JunkValue = 1;

	//Shooting시 힘을 정의합니다. 높으면 높을수록 강하게 던져집니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent", meta = (EditCondition = "InteractiveType == EInteractiveType::Rigid", EditConditionHides))
	float					ShootingPowerValue = 2000.f;

	//이름의 Type을 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent", meta = (EditCondition = "InteractiveComponentToType == EInteractiveComponentToType::Setup", EditConditionHides))
	ENameType				NameType;

	//Move Action을 수행할 Component의 이름일 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent", meta = (EditCondition = "InteractiveComponentToType == EInteractiveComponentToType::Setup", EditConditionHides))
	FName					InteractiveName;

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|InteractiveObjectComponent")
	TArray<TSoftObjectPtr<UPrimitiveComponent>>	AffectInteractiveComponents;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void UpdateInteractiveAction(EInteractiveAction NextInteractiveAction, EInteractiveAction BeforeInteractiveAction) override;
	virtual bool CanUpdateInteractive(EInteractiveAction NextInteractiveAction, EInteractiveAction CurrentInteractiveAction) override;
};
