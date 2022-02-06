// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTriggerComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "CapabilitySystemComponent.h"
#include "../../GAS/Interface/Actor/GASActorInterface.h"
#include "../Interactive/Classes/InteractiveSuckingComponent.h"
#include "../../GAS/Ability/BaseGameplayAbility.h"
#include "../../Components/Utility/ComponentFunctionLibrary.h"
#include "BodyCleanup/GAS/Effect/BaseGameplayEffect.h"
#include "LevelDesignerTools/Actor/LevelToolsActorInterface.h"
#include "LevelDesignerTools/Actor/Assist/LevelTriggerActorAssist.h"
#include "LevelDesignerTools/GameMode/LevelToolsGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "LevelDesignerTools/Trigger/Managers/LevelTriggerManager.h"
#include "LevelDesignerTools/Trigger/Classes/Scene/HitTriggerComponent.h"
#include "../../GCS/Effect/BaseCAPEffect.h"
#include "../../GCS/Interface/GCSActorInterface.h"
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

//		const ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(Cast<ILevelTriggerInterface>(this));
//
//		if(IsValid(LevelTriggerInterfaceSpace))
//		{
//			TArray<TSoftObjectPtr<UPrimitiveComponent>> TriggerPrimitiveComponents;
//
//			LevelTriggerInterfaceSpace->GetTriggerPrimitiveComponents(TriggerPrimitiveComponents);				
//
//			for(TSoftObjectPtr<UPrimitiveComponent> Key : TriggerPrimitiveComponents)
//			{
//				if(Key.IsValid())
//				{
//					const FLevelTriggerCertificate* LevelTriggerCertificate = LevelTriggerInterfaceSpace->GetLevelTriggerCertificate(Key.Get());
//
//					if(nullptr != LevelTriggerCertificate)
//					{
//						for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : LevelTriggerCertificate->OtherComps)
//						{
//							if(PrimitiveComponent.IsValid())
//							{
//								AActor* TargetComponentOwner = PrimitiveComponent->GetOwner();
//
//								if(__CanDamageInteractiveActor(TargetComponentOwner))
//								{
//									TargetActors.AddUnique(TargetComponentOwner);
//								}
//							}
//						}
//					}						
//				}
//			}
//		}
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
		//if(Owner->GetClass()->ImplementsInterface(ULevelToolsActorInterface::StaticClass()))
		//{
		//	ULevelTriggerActorAssist* LevelTriggerActorAssist = Cast<ILevelToolsActorInterface>(Owner)->GetLevelTriggerActorAssist();
		//}

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

								for(AActor* TargetActor : TargetActors)
								{
									CapabilitySystemComponent->ApplyGameplayEffectToTarget(HoldShootingGameplayEffect, Cast<ICapabilitySystemInterface>(TargetActor)->GetCapabilitySystemComponent(), 0);
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
