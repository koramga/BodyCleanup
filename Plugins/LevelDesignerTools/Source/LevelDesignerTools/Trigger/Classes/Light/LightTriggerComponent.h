// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actor/TriggerActorComponent.h"
#include "LightTriggerComponent.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FLightTriggerParam
{
	GENERATED_BODY()

public :
	FLightTriggerParam();
	FLightTriggerParam(const TSoftObjectPtr<ULightComponent>& InLightComponent);

	TSoftObjectPtr<ULightComponent> LightComponent;
	float Intensity = 0.f;
	FLinearColor	LightColor;

	void Reset();
};

UENUM(BlueprintType)
enum class ELightTriggerIntensitySignType : uint8
{
	Sin,
	Cos,
	Curve,
};

USTRUCT(BlueprintType)
struct FLightTriggerIntensityParam
{
	GENERATED_BODY()	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELightTriggerIntensitySignType	IntensitySignType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float							Intensity = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "IntensitySignType == ELightTriggerIntensitySignType::Curve", EditConditionHides))
	UCurveFloat*					CurveFloat;
};

USTRUCT(BlueprintType)
struct FLightTriggerColorParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCurveLinearColor*				CurveLinearColor;
};

UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API ULightTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	ULightTriggerComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|LightTriggerComponent")
	FLevelTriggerInputTo			LevelTriggerInputTo;
	
	//시간의 속도를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|LightTriggerComponent")
	float							TimeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|LightTriggerComponent")
	bool							bIsUpdateIntensity;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|LightTriggerComponent", meta = (EditCondition = "bIsUpdateIntensity", EditConditionHides))
	FLightTriggerIntensityParam		LightTriggerIntensityParam;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|LightTriggerComponent")
	bool							bIsUpdateColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|LightTriggerComponent", meta = (EditCondition = "bIsUpdateColor", EditConditionHides))
	FLightTriggerColorParam			LightTriggerColorParam;
	
protected:
	UPROPERTY()
	TArray<FLightTriggerParam>		LightTriggerParams;
	
	float RunningTime;

protected:
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

protected:
	virtual void UpdateIntensity(float InTime);
	virtual void UpdateColor(float InTime);

public :
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
