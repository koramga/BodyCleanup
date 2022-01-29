// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTriggerComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "../../GAS/Interface/Actor/GASActorInterface.h"
#include "../Interactive/Classes/InteractiveSuckingComponent.h"
#include "../../Utilities/FunctionLibraries/FindFunctionLibrary.h"
#include "../../GAS/Ability/BaseGameplayAbility.h"

UDamageTriggerComponent::UDamageTriggerComponent()
{
	
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

	if (true == InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		AActor* Owner = GetOwner();

		if(IsValid(Owner))
		{
			bool bImplementationAbilitySystem = Owner->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass());
			bool bImplementationGAS = Owner->GetClass()->ImplementsInterface(UGASActorInterface::StaticClass());

			if(true == bImplementationAbilitySystem
				&& true == bImplementationGAS)
			{
				TSoftObjectPtr<UInteractiveSuckingComponent> InteractiveSuckingComponent = UFindFunctionLibrary::FindInteractiveSuckingComponent(Owner);

				if(InteractiveSuckingComponent.IsValid())
				{
					//Shoot인지 확인한다.
					const TSubclassOf<UBaseGameplayAbility>& HoldShootingAbility = InteractiveSuckingComponent->GetHoldShootingAbility();
					
					if(IsValid(HoldShootingAbility))
					{
						EInteractiveSuckingType InteractiveSuckingType = InteractiveSuckingComponent->GetInteractiveSuckingType();

						if(EInteractiveSuckingType::HoldShooting == InteractiveSuckingType)
						{
							//Effect를 넣는다.
							UAbilitySystemComponent* AbilitySystemComponent = Cast<IAbilitySystemInterface>(Owner)->GetAbilitySystemComponent();

							AbilitySystemComponent->TryActivateAbilityByClass(HoldShootingAbility, true);
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

void UDamageTriggerComponent::UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam)
{
	Super::UpdateAction(LevelTriggerUpdateActionParam);
}
