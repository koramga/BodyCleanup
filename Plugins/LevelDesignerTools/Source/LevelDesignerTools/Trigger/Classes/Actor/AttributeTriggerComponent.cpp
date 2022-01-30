// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeTriggerComponent.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"

UAttributeTriggerComponent::UAttributeTriggerComponent()
{

}

void UAttributeTriggerComponent::ExecuteTriggerAction(const FLevelAttributeTriggerAction& ExecuteAction)
{
	TArray<TSoftObjectPtr<UActorComponent>> Components;
	
	if(ExecuteAction.bIsTag)
	{
		ULevelSupportFunctionLibrary::FindComponentsByTags(Components, GetOwner(), ExecuteAction.Names);
	}
	else
	{
		ULevelSupportFunctionLibrary::FindComponentsByNames(Components, GetOwner(), ExecuteAction.Names);
	}

	for(const TSoftObjectPtr<UActorComponent>& Component : Components)
	{
		if(Component.IsValid())
		{
			if(ELevelAttributeTriggerActionType::Visible == ExecuteAction.ActionType)
			{
				USceneComponent* SceneComponent = Cast<USceneComponent>(Component.Get());

				if(IsValid(SceneComponent))
				{
					SceneComponent->SetHiddenInGame(false);

					if(SceneComponent->IsA(UPrimitiveComponent::StaticClass()))
					{
						Cast<UPrimitiveComponent>(SceneComponent)->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					}
					
					//SceneComponent->SetVisibility(true, true);
				}
			}
			else if(ELevelAttributeTriggerActionType::InVisible == ExecuteAction.ActionType)
			{
				USceneComponent* SceneComponent = Cast<USceneComponent>(Component.Get());

				if(IsValid(SceneComponent))
				{
					SceneComponent->SetHiddenInGame(true);

					if(SceneComponent->IsA(UPrimitiveComponent::StaticClass()))
					{
						Cast<UPrimitiveComponent>(SceneComponent)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					}
					
					//SceneComponent->SetVisibility(false, true);
				}				
			}
		}
	}
}

void UAttributeTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	for(const FLevelAttributeTriggerAction& LevelAttributeTriggerAction : LevelAttributeTriggerActions)
	{
		if(MaxTriggerIndex < LevelAttributeTriggerAction.TriggerIndex)
		{
			MaxTriggerIndex = LevelAttributeTriggerAction.TriggerIndex;
		}

		if(LevelAttributeTriggerAction.TriggerIndex == 0)
		{
			ExecuteTriggerAction(LevelAttributeTriggerAction);			
		}
	}

	CurrentTriggerIndex = 1;
}

void UAttributeTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UAttributeTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if(InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		if(CurrentTriggerIndex <= MaxTriggerIndex)
		{	
			for(const FLevelAttributeTriggerAction& LevelAttributeTriggerAction : LevelAttributeTriggerActions)
			{
				if(LevelAttributeTriggerAction.TriggerIndex == CurrentTriggerIndex)
				{
					ExecuteTriggerAction(LevelAttributeTriggerAction);
				}
			}
		
			CurrentTriggerIndex++;
		}		
	}	
}