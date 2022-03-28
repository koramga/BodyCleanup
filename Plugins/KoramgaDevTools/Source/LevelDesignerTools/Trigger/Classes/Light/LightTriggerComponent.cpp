// Fill out your copyright notice in the Description page of Project Settings.


#include "LightTriggerComponent.h"

#include "Components/LightComponent.h"
#include "Curves/CurveLinearColor.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

FLightTriggerParam::FLightTriggerParam()
{
}

FLightTriggerParam::FLightTriggerParam(const TSoftObjectPtr<ULightComponent>& InLightComponent)
{
	LightComponent = InLightComponent;
	Intensity = InLightComponent->Intensity;
	LightColor = InLightComponent->GetLightColor();
}

void FLightTriggerParam::Reset()
{
	if(LightComponent.IsValid())
	{
		LightComponent->SetIntensity(Intensity);
		LightComponent->SetLightColor(LightColor);
	}	
}

ULightTriggerComponent::ULightTriggerComponent()
{
	TimeSpeed = 1.f;
	bIsUpdateIntensity = false;
	bIsUpdateColor = false;
	PrimaryComponentTick.bCanEverTick = true;
}

void ULightTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
}

void ULightTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();

	if (ELevelTriggerInputNodeToType::Setup == LevelTriggerInputTo.LevelTriggerInputNodeToType)
	{
		for (const FLevelTriggerInputNode& LevelTriggerInputNode : LevelTriggerInputTo.LevelTriggerInputNodes)
		{
			TArray<TSoftObjectPtr<UActorComponent>> ActorComponents;

			if (false == LevelTriggerInputNode.bIsTag)
			{
				ULevelSupportFunctionLibrary::FindComponentsByNames(ActorComponents, GetOwner(), LevelTriggerInputNode.Names);
			}
			else
			{
				ULevelSupportFunctionLibrary::FindComponentsByTags(ActorComponents, GetOwner(), LevelTriggerInputNode.Names);
			}

			for (TSoftObjectPtr<UActorComponent> ActorComponent : ActorComponents)
			{
				USceneComponent* LightComponent = Cast<ULightComponent>(ActorComponent.Get());

				if (IsValid(LightComponent))
				{
					LightTriggerParams.Add(FLightTriggerParam(LightComponent));
				}
			}
		}
	}
}

void ULightTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if(true == InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		SetComponentTickEnabled(true);
		RunningTime = 0.f;
	}
	else
	{
		SetComponentTickEnabled(false);
		
		for(FLightTriggerParam& LightTriggerParam : LightTriggerParams)
		{
			LightTriggerParam.Reset();
		}
	}
}

void ULightTriggerComponent::UpdateIntensity(float InTime)
{	
	float Value = 0.f;
	
	if(ELightTriggerIntensitySignType::Sin == LightTriggerIntensityParam.IntensitySignType)
	{
		Value = FMath::Sin(RunningTime);
	}
	else if(ELightTriggerIntensitySignType::Cos == LightTriggerIntensityParam.IntensitySignType)
	{
		Value = FMath::Cos(RunningTime);
	}
	else if(ELightTriggerIntensitySignType::Curve == LightTriggerIntensityParam.IntensitySignType)
	{
		if(IsValid(LightTriggerIntensityParam.CurveFloat))
		{
			float MinTime, MaxTime;
		
			LightTriggerIntensityParam.CurveFloat->GetTimeRange(MinTime, MaxTime);

			float TimeValue = MinTime + RunningTime;
			int DivTimeValue = static_cast<int>(TimeValue / MaxTime);
			TimeValue -= DivTimeValue * MaxTime;
		
			Value = LightTriggerIntensityParam.CurveFloat->GetFloatValue(TimeValue);			
		}		
	}
	
	for(FLightTriggerParam& LightTriggerParam : LightTriggerParams)
	{
		if(LightTriggerParam.LightComponent.IsValid())
		{
			LightTriggerParam.LightComponent->SetIntensity(LightTriggerParam.Intensity + Value * LightTriggerIntensityParam.Intensity);
		}
	}
}

void ULightTriggerComponent::UpdateColor(float InTime)
{	
	if(IsValid(LightTriggerColorParam.CurveLinearColor))
	{
		float MinTime, MaxTime;
		
		LightTriggerColorParam.CurveLinearColor->GetTimeRange(MinTime, MaxTime);

		float TimeValue = MinTime + RunningTime;
		int DivTimeValue = static_cast<int>(TimeValue / MaxTime);
		TimeValue -= DivTimeValue * MaxTime;
		
		FLinearColor Value = LightTriggerColorParam.CurveLinearColor->GetLinearColorValue(TimeValue);

		for(FLightTriggerParam& LightTriggerParam : LightTriggerParams)
		{
			if(LightTriggerParam.LightComponent.IsValid())
			{
				LightTriggerParam.LightComponent->SetLightColor(Value);
			}
		}
	}	
}

void ULightTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RunningTime += (DeltaTime * TimeSpeed);

	if(bIsUpdateIntensity)
	{
		UpdateIntensity(RunningTime);
	}

	if(bIsUpdateColor)
	{
		UpdateColor(RunningTime);
	}
}
