// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerSceneComponent.h"
#include "HitTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UHitTriggerComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()

public :
	UHitTriggerComponent();

protected:
	//1초 뒤에 결과가 도착할 예정이므로 배속을 결정합니다. (값이 0.5이면 도착까지 걸리는 시간이 2초가 된다는 의미입니다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	float	InterpSpeed = 1.f;

	//Action의 범위를 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	FLevelTriggerInputTo	LevelTriggerInputTo;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
	virtual bool IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult) override;
};
