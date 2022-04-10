// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerSceneComponent.h"
#include "HitComponentTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UHitComponentTriggerComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()

public :
	UHitComponentTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
	virtual bool IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult) override;
};
