// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCapabilitySystemComponent.h"
#include "../../ExDefines.h"
#include "../../Components/Actor/GameActorSettingsComponent.h"

bool UBaseCapabilitySystemComponent::ApplyGameplayEffectToTargetWithAdvantage(UCAPEffect* CAPEffect,
                                                                              UCapabilitySystemComponent* Target, int32 AbilityLevel)
{
	AActor* Owner = GetOwner();
	AActor* TargetOwner = Target->GetOwner();

	if(false == IsValid(Owner)
		|| false == IsValid(TargetOwner))
	{
		return Super::ApplyGameplayEffectToTarget(CAPEffect, Target, AbilityLevel);
	}

	UGameActorSettingsComponent* GameActorSettingsComponent = Cast<UGameActorSettingsComponent>(Owner->GetComponentByClass(UGameActorSettingsComponent::StaticClass()));
	UGameActorSettingsComponent* TagetGameActorSettingComponent = Cast<UGameActorSettingsComponent>(TargetOwner->GetComponentByClass(UGameActorSettingsComponent::StaticClass()));

	if(nullptr == GameActorSettingsComponent
		|| nullptr == TagetGameActorSettingComponent)
	{
		return Super::ApplyGameplayEffectToTarget(CAPEffect, Target, AbilityLevel);
	}

	TArray<FCAPEffectAdvantage> Advantages;
	
	EWeightType WeightType = GameActorSettingsComponent->GetWeightType();
	EWeightType TargetWeightType = TagetGameActorSettingComponent->GetWeightType();
	float Advantage = 1.f;

	switch (WeightType)
	{
	case EWeightType::Dust :
		if(TargetWeightType == EWeightType::Dust)
		{
			
		}
		else
		{
			Advantage = 0.f;
		}
		break;
	case EWeightType::Light :
		if(TargetWeightType == EWeightType::Dust
			|| TargetWeightType == EWeightType::Light)
		{

		}
		else if(TargetWeightType == EWeightType::Middle)
		{
			Advantage = 0.5f;
		}
		else
		{
			Advantage = 0.f;
		}
		break;
	case EWeightType::Middle :
		if(TargetWeightType == EWeightType::Dust
			|| TargetWeightType == EWeightType::Light
			|| TargetWeightType == EWeightType::Middle)
		{

		}
		else if(TargetWeightType == EWeightType::Heavy)
		{
			Advantage = 0.5f;
		}
		else
		{
			Advantage = 0.f;
		}
		break;
	case EWeightType::Heavy :
		if(TargetWeightType == EWeightType::Dust
			|| TargetWeightType == EWeightType::Light
			|| TargetWeightType == EWeightType::Middle
			|| TargetWeightType == EWeightType::Heavy)
		{
			
		}
		else
		{
			Advantage = 0.f;
		}
		break;
	case EWeightType::Structure :
		break;
	}
	
	Advantages.Add(FCAPEffectAdvantage("Health", Advantage));
	return Super::ApplyGameplayEffectToTarget(CAPEffect, Target, AbilityLevel, &Advantages);
}
