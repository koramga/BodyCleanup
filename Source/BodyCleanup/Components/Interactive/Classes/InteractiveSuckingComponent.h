// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractiveTriggerComponent.h"
#include "InteractiveSuckingComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Interactive), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UInteractiveSuckingComponent : public UInteractiveTriggerComponent
{
	GENERATED_BODY()

public :
	UInteractiveSuckingComponent();

protected :
	//Sucking의 속도를 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent")
	float					SuckingPower = 500.f;

	//흡수되는 정크의 양을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent")
	int32					JunkValue = 1;

	//HoldShooting시 힘을 정의합니다. 높으면 높을수록 강하게 던져집니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent", meta = (EditCondition = "JunkValue <= 0", EditConditionHides))
	float					HoldShootingPower = 2000.f;

	//Trigger를 수행할 InteractiveSuckingType을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent")
	TArray<EInteractiveSuckingType>	TriggerInteractiveSuckingTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent", meta = (EditCondition = "JunkValue <= 0", EditConditionHides))
	TSubclassOf<class UBaseGameplayAbility>		BaseGameplayAbilityClass;

	//Tag 유무를 선택합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent")
	bool							bIsTag;

	//영향을 받을 Component의 이름을 입력합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveObjectComponent")
	TArray<FName>					Names;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UPrimitiveComponent>>	PrimitiveComponents;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected :
	virtual bool CanUpdateInteractiveType(uint8 CurrentInteractiveType, uint8 DesiredInteractiveType) override;
	virtual void UpdateInteractiveType(uint8 CurrentInteractiveType, uint8 BeforeInteractiveType) override;

public :
	EInteractiveSuckingType GetInteractiveSuckingType() const;
	bool SetSucking(USceneComponent* SceneComponent);
	bool SetHoldShooting(USceneComponent* SceneComponent);
	bool SetHolding(USceneComponent* SceneComponent);
	bool SetNone(USceneComponent* SceneComponent);
	
public :
	bool IsJunk() const;
	int32 GetJunkValue() const;
};
