// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialTriggerComponent.h"

#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

UMaterialTriggerComponent::UMaterialTriggerComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;
}

void UMaterialTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
}

void UMaterialTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
	
	if (ELevelTriggerInputNodeToType::Parent == LevelTriggerInputTo.LevelTriggerInputNodeToType)
	{
		USceneComponent* AttachParentComponent = GetAttachParent();

		if (IsValid(AttachParentComponent))
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(AttachParentComponent);

			if(IsValid(PrimitiveComponent))
			{
				PrimitiveComponents.Add(PrimitiveComponent);
			}			
		}
	}
	else if (ELevelTriggerInputNodeToType::Setup == LevelTriggerInputTo.LevelTriggerInputNodeToType)
	{
		for (const FLevelTriggerInputNode& LevelTriggerInputNode : LevelTriggerInputTo.LevelTriggerInputNodes)
		{
			TArray<TSoftObjectPtr<UPrimitiveComponent>> ActorComponents;

			if (false == LevelTriggerInputNode.bIsTag)
			{
				ULevelSupportFunctionLibrary::FindPrimitiveComponentsByNames(PrimitiveComponents, GetOwner(), LevelTriggerInputNode.Names);
			}
			else
			{
				ULevelSupportFunctionLibrary::FindPrimitiveComponentsByNames(PrimitiveComponents, GetOwner(), LevelTriggerInputNode.Names);
			}
		}
	}
}

void UMaterialTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if(true == InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		if(false == IsComponentTickEnabled())
		{
			SetComponentTickEnabled(true);
		}

		MaterialTickTime = 0.f;
	}
}

void UMaterialTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(MaterialTickTime < MaterialUpdateKeepTime)
	{
		if(MaterialTickTime == 0.f
			&& BackupMetaVariables.Num() == 0)
		{
			//최초 구간!

			for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
			{
				if(PrimitiveComponent.IsValid())
				{
					for(const FMaterialInstanceVariable& MaterialInstanceVariable : MaterialInstanceVariables)
					{
						BackupMetaVariables.Add(MaterialInstanceVariable.GetMaterialInstanceParameter(PrimitiveComponent.Get()));
						MaterialInstanceVariable.SetMaterialInstanceParameter(PrimitiveComponent.Get());
					}
				}
			}			
		}
		
		MaterialTickTime += DeltaTime;		
	}
	else
	{
		//경과 종료!

		for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
		{
			if(PrimitiveComponent.IsValid())
			{
				for(int i = 0; i < MaterialInstanceVariables.Num(); ++i)
				{
					const FMaterialInstanceVariable& MaterialInstanceVariable = MaterialInstanceVariables[i];
					MaterialInstanceVariable.SetMaterialInstanceParameter(PrimitiveComponent.Get(), BackupMetaVariables[i]);
				}
			}
		}
			
		BackupMetaVariables.Reset();
		
		SetComponentTickEnabled(false);
	}
}