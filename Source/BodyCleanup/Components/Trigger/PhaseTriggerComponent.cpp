// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseTriggerComponent.h"

#include "CapabilitySystemComponent.h"
#include "CapabilitySystemInterface.h"
#include "BodyCleanup/Character/NPCCharacter/BaseNPCCharacter.h"
#include "BodyCleanup/Game/GameInstance/BaseGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "LevelDesignerTools/GameMode/LevelToolsGameModeBase.h"

UPhaseTriggerComponent::UPhaseTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	LevelTriggerInputFrom.LevelTriggerInputNodeFromType = ELevelTriggerInputNodeFromType::Action;
}

void UPhaseTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	BaseNPCCharacter = Cast<ABaseNPCCharacter>(GetOwner());

	if(BaseNPCCharacter.IsValid())
	{
		if(GetOwner()->GetClass()->ImplementsInterface(UCapabilitySystemInterface::StaticClass()))
		{
			CapabilitySystemComponent = Cast<ICapabilitySystemInterface>(GetOwner())->GetCapabilitySystemComponent();

			if(CapabilitySystemComponent.IsValid())
			{	
				UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetAuthGameMode()->GetGameInstance());

				if(IsValid(BaseGameInstance))
				{
					MaxHPStatName = BaseGameInstance->GetStatTypeToName(EGameStatType::MaxHP);
					FCAPAttributeData* MaxHPAttributeData = CapabilitySystemComponent->GetAttributeDataByAttributeName(MaxHPStatName);

					HPStatName = BaseGameInstance->GetStatTypeToName(EGameStatType::HP);
					FCAPAttributeData* HPAttributeData = CapabilitySystemComponent->GetAttributeDataByAttributeName(HPStatName);

					if(nullptr != MaxHPAttributeData
						&& nullptr != HPAttributeData)
					{
						SetComponentTickEnabled(true);
					}
				}			
			}
		}		
	}	
}

void UPhaseTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UPhaseTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
}

void UPhaseTriggerComponent::UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam)
{
	Super::UpdateAction(LevelTriggerUpdateActionParam);
}

void UPhaseTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(BaseNPCCharacter.IsValid())
	{
		if(CapabilitySystemComponent.IsValid())
		{
			FCAPAttributeData* MaxHPAttributeData = CapabilitySystemComponent->GetAttributeDataByAttributeName(MaxHPStatName);
			FCAPAttributeData* HPAttributeData = CapabilitySystemComponent->GetAttributeDataByAttributeName(HPStatName);
		
			if(HPAttributeData != nullptr
				&& MaxHPAttributeData != nullptr)
			{
				float MaxHP = MaxHPAttributeData->GetCurrentValue();
				float HP = HPAttributeData->GetCurrentValue();

				for(int i = BaseNPCCharacter->GetPhase(); i < PhaseInputs.Num(); ++i)
				{
					if(MaxHP * PhaseInputs[i].HPPercent > HP)
					{
						ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

						if (nullptr != LevelToolsGameModeBase)
						{
							LevelToolsGameModeBase->UpdateTriggerOnce(this);
						}
						
						BaseNPCCharacter->SetPhase(i + 1);
						break;
					}
				}

				if(BaseNPCCharacter->GetPhase() == PhaseInputs.Num())
				{
					SetComponentTickEnabled(false);
				}
			}
		}
		else
		{
			SetComponentTickEnabled(false);
		}		
	}
	else
	{
		SetComponentTickEnabled(false);
	}
	
}
