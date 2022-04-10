// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTriggerComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "CapabilitySystemComponent.h"
#include "../../GAS/Interface/Actor/GASActorInterface.h"
#include "../Interactive/Classes/InteractiveSuckingComponent.h"
#include "../../GAS/Ability/BaseGameplayAbility.h"
#include "../../Components/Utility/ComponentFunctionLibrary.h"
#include "LevelDesignerTools/GameMode/LevelToolsGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "LevelDesignerTools/Trigger/Managers/LevelTriggerManager.h"
#include "../../GCS/Effect/BaseCAPEffect.h"
#include "../../GCS/Interface/GCSActorInterface.h"
#include "../../GCS/Component/BaseCapabilitySystemComponent.h"
#include "CapabilitySystemInterface.h"

UDamageTriggerComponent::UDamageTriggerComponent()
{
	
}

void UDamageTriggerComponent::__FindTargetActors(TArray<AActor*>& TargetActors) const
{
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();

	if (GameModeBase->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
	{
		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GameModeBase);

		const ULevelTriggerManager* LevelTriggerManager = LevelToolsGameModeBase->GetLevelTriggerManager();

		TArray<TSoftObjectPtr<AActor>> OverlapActors;
		
		LevelTriggerManager->FindOverlapActors(OverlapActors, Cast<ILevelTriggerInterface>(this));

		for(TSoftObjectPtr<AActor> OverlapActor : OverlapActors)
		{
			if(__CanDamageInteractiveActor(OverlapActor.Get()))
			{
				TargetActors.AddUnique(OverlapActor.Get());
			}
		}
	}	
}

bool UDamageTriggerComponent::__CanDamageInteractiveActor(const AActor* Actor) const
{
	bool bImplementationCapabilitySystem = Actor->GetClass()->ImplementsInterface(UCapabilitySystemInterface::StaticClass());
	bool bImplementationGCS = Actor->GetClass()->ImplementsInterface(UGCSActorInterface::StaticClass());

	if(bImplementationCapabilitySystem
		&& bImplementationGCS)
	{
		return true;
	}

	return false;
}

void UDamageTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDamageTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UDamageTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
	
	AActor* Owner = GetOwner();

	if(IsValid(Owner))
	{
		if (true == InputLevelTriggerUpdateParam.bIsOnTrigger)
		{
			TArray<AActor*>		TargetActors;

			__FindTargetActors(TargetActors);

			if(TargetActors.Num() > 0)
			{
				if(__CanDamageInteractiveActor(Owner))
				{
					TSoftObjectPtr<UInteractiveSuckingComponent> InteractiveSuckingComponent = UComponentFunctionLibrary::FindInteractiveSuckingComponent(Owner);

					if(InteractiveSuckingComponent.IsValid())
					{
						//Shoot인지 확인한다.
						UBaseCAPEffect* HoldShootingGameplayEffect = InteractiveSuckingComponent->GetHoldShootingCAPEffect();
					
						if(IsValid(HoldShootingGameplayEffect))
						{
							EInteractiveSuckingType InteractiveSuckingType = InteractiveSuckingComponent->GetInteractiveSuckingType();

							if(EInteractiveSuckingType::HoldShooting == InteractiveSuckingType)
							{
								//Effect를 넣는다.
								UCapabilitySystemComponent* CapabilitySystemComponent = Cast<ICapabilitySystemInterface>(Owner)->GetCapabilitySystemComponent();
								UBaseCapabilitySystemComponent* BaseCapabilitySystemComponent = Cast<UBaseCapabilitySystemComponent>(CapabilitySystemComponent);

								for(AActor* TargetActor : TargetActors)
								{
									if(IsValid(BaseCapabilitySystemComponent))
									{
										BaseCapabilitySystemComponent->ApplyGameplayEffectToTargetWithAdvantage(HoldShootingGameplayEffect, Cast<ICapabilitySystemInterface>(TargetActor)->GetCapabilitySystemComponent());	
									}
									else
									{
										CapabilitySystemComponent->ApplyGameplayEffectToTarget(HoldShootingGameplayEffect, Cast<ICapabilitySystemInterface>(TargetActor)->GetCapabilitySystemComponent());										
									}									
								}		
							}						
						}					
					}
				}			
			}
		}
		else
		{
			
		}
	}
}

void UDamageTriggerComponent::UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam)
{
	Super::UpdateAction(LevelTriggerUpdateActionParam);
}
