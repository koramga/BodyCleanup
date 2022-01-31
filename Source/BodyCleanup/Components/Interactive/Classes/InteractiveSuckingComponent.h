// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayAbilitySpec.h"
#include "GameplayEffect.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent")
	float					SuckingPower = 500.f;

	//Trigger를 수행할 InteractiveSuckingType을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent")
	TArray<EInteractiveSuckingType>	TriggerInteractiveSuckingTypes;

	//Tag 유무를 선택합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent")
	bool							bIsTag;

	//영향을 받을 Component의 이름을 입력합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent")
	TArray<FName>					Names;

	//Sucking시 Holding이 되는지 유무입니다. True이면 Holding, False이면 삭제됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent")
	bool					bCanHolding = true;

	//흡수되는 정크의 양을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent", meta = (EditCondition = "!bCanHolding", EditConditionHides))
	int32					JunkValue = 1;

	//HoldShooting시 힘을 정의합니다. 높으면 높을수록 강하게 던져집니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent", meta = (EditCondition = "bCanHolding", EditConditionHides))
	float					HoldShootingPower = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveSuckingComponent", meta = (EditCondition = "bCanHolding", EditConditionHides))
	TSubclassOf<class UBaseGameplayEffect>		BaseGameplayEffectClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UPrimitiveComponent>>	PrimitiveComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAbilitySpec						HoldShootingAbilitySpec;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseGameplayEffect*					BaseGameplayEffect;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected :
	virtual bool CanUpdateInteractiveType(uint8 CurrentInteractiveType, uint8 DesiredInteractiveType) override;
	virtual void UpdateInteractiveType(uint8 CurrentInteractiveType, uint8 BeforeInteractiveType) override;
	virtual void SetRigidBodyCollision(bool bIsCollision);
	
public :
	EInteractiveSuckingType GetInteractiveSuckingType() const;
	bool SetSucking(USceneComponent* SceneComponent);
	bool SetHoldShooting(USceneComponent* SceneComponent);
	bool SetHolding(USceneComponent* SceneComponent);
	bool SetNone(USceneComponent* SceneComponent);
	
public :
	bool IsJunk() const;
	int32 GetJunkValue() const;
	const FGameplayAbilitySpec& GetHoldShootingAbilitySpec() const;
	UBaseGameplayEffect* GetHoldShootingGameplayEffect();		
};
