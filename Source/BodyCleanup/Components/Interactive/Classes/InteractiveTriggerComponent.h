// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../ExDefines.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/StateTriggerComponent.h"
#include "../Interfaces/InteractiveComponentInterface.h"
#include "InteractiveTriggerComponent.generated.h"

/**
 * 
 */

UCLASS()
class BODYCLEANUP_API UInteractiveTriggerComponent : public UStateTriggerComponent, public IInteractiveComponentInterface
{
	GENERATED_BODY()

public :
	UInteractiveTriggerComponent();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 InteractiveType;

protected:
	virtual void BeginPlay() override;

public :
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void SetInteractiveType(uint8 InputInteractiveType);
	virtual bool CanUpdateInteractiveType(uint8 CurrentInteractiveType, uint8 DesiredInteractiveType);
	virtual void UpdateInteractiveType(uint8 CurrentInteractiveType, uint8 BeforeInteractiveType);
	
public:
	virtual bool UpdateInteractiveType(uint8 InputInteractiveType) override;
	virtual uint8 GetInteractiveType() const override;
	virtual bool CanUpdateInteractiveType(uint8 InputInteractiveType) override;
};
