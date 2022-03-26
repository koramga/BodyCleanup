// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCapabilitySystemComponent.h"
#include "../../ExDefines.h"
#include "../../Components/Actor/GameActorSettingsComponent.h"
#include "../../Game/GameInstance/BaseGameInstance.h"
#include "../../Game/GameMode/BaseGameModeBase.h"
#include "BodyCleanup/GCS/Ability/BaseCAPAbility.h"

bool UBaseCapabilitySystemComponent::ApplyGameplayEffectToTargetWithAdvantage(TSoftObjectPtr<UCAPEffect> CAPEffect,
                                                                              UCapabilitySystemComponent* Target, int32 AbilityLevel, float Weight)
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
	
	UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetAuthGameMode()->GetGameInstance());
	
	if(IsValid(BaseGameInstance))
	{
		FName StatTypeName = BaseGameInstance->GetStatTypeToName(EGameStatType::HP);
		
		Advantages.Add(FCAPEffectAdvantage(StatTypeName, Advantage));
	}

	if(Super::ApplyGameplayEffectToTarget(CAPEffect, Target, AbilityLevel, Weight, &Advantages))
	{
	 	int32 WeightTypeIndex = static_cast<int32>(WeightType);
		int32 TargetWeightTypeIndex = static_cast<int32>(TargetWeightType);

		if(WeightTypeIndex <= TargetWeightTypeIndex)
		{
			Target->ApplyGameplayEffectToTarget(CAPEffect, this, AbilityLevel);	
		}

		return true;
	}

	return false;
}

void UBaseCapabilitySystemComponent::LeftAnimationType(EAnimationType AnimationType)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		UBaseCAPAbility* BaseCAPAbility = Cast<UBaseCAPAbility>(CAPAbility);

		if(IsValid(BaseCAPAbility))
		{
			BaseCAPAbility->LeftAnimationType(AnimationType);
		}
	}
}

float UBaseCapabilitySystemComponent::GetAbilityRangeByTag(const FGameplayTag& Tag)
{
	for (UCAPAbility* CAPAbility : CAPAbilities)
	{
		if (CAPAbility->IsAbilityTag(Tag))
		{
			float AbilityRange = 0.f;

			UBaseCAPAbility* BaseCAPAbility = Cast<UBaseCAPAbility>(CAPAbility);

			if (IsValid(BaseCAPAbility))
			{
				AbilityRange = BaseCAPAbility->GetAbilityRange();
			}

			return AbilityRange;
		}
	}

	return 0.f;
}
