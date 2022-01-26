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
	//1�� �ڿ� ����� ������ �����̹Ƿ� ����� �����մϴ�. (���� 0.5�̸� �������� �ɸ��� �ð��� 2�ʰ� �ȴٴ� �ǹ��Դϴ�.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	float	InterpSpeed = 1.f;

	//Action�� ������ �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ComponentMovementComponent")
	FLevelTriggerInputTo	LevelTriggerInputTo;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
	virtual bool IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult) override;
};
