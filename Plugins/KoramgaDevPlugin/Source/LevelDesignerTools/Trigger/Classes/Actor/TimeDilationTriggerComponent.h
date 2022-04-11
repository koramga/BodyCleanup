// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "TimeDilationTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UTimeDilationTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UTimeDilationTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

public :
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|TimeDilationTriggerComponent", meta=(ClampMin="0.0", ClampMax="10.0",UIMin="0.0",UIMax="10.0"))
	float TimeDilation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|TimeDilationTriggerComponent", meta=(ClampMin="0.0", UIMin="0.0"))
	float KeepTime = 0.2f;

	float TickTime = 0.f;
};
