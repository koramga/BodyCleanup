﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerComponent.h"
#include "Interfaces/LevelActionInterface.h"
#include "ActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UActionComponent : public UTriggerComponent, public ILevelActionInterface
{
	GENERATED_BODY()

public :
	UActionComponent();

protected :
	//TickTock Type을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ActionComponent")
	EActionComponentActionType	ActionType;

protected :
	//사용자가 원하는 형태로의 변형이 이루어지고 있는지를 판단한다. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|ActionComponent")
	bool						bIsUpdateDestinationTransformed = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	virtual void OnTrigger(bool bInputIsOnTrigger) override;

protected :
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;
	
public :
	bool IsUpdateDestinationTransformed() const;
};
