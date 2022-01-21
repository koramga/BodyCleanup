// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentMovementComponent.h"
//#include "../../Utilities/FunctionLibraries/FindFunctionLibrary.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"

UComponentMovementComponent::UComponentMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DestinationDeltaTransform.SetLocation(FVector(0.f, 0.f, 0.f));
	DestinationDeltaTransform.SetRotation(FRotator(0.f, 0.f, 0.f).Quaternion());
	DestinationDeltaTransform.SetScale3D(FVector(0.f, 0.f, 0.f));
}

void UComponentMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UComponentMovementComponent::SetupTrigger()
{
	if (ELevelTriggerInputNodeToType::Parent == LevelTriggerInputTo.LevelTriggerInputNodeToType)
	{
		USceneComponent* AttachParentComponent = GetAttachParent();

		if (IsValid(AttachParentComponent))
		{
			ComponentMovementDatas.Add(FComponentMovementData(AttachParentComponent));
		}
	}
	else if (ELevelTriggerInputNodeToType::Setup == LevelTriggerInputTo.LevelTriggerInputNodeToType)
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
				USceneComponent* SceneComponent = Cast<USceneComponent>(ActorComponent.Get());

				if (IsValid(SceneComponent))
				{
					ComponentMovementDatas.Add(FComponentMovementData(SceneComponent));
				}
			}
		}
	}

	for (FComponentMovementData& ComponentMovementData : ComponentMovementDatas)
	{
		ComponentMovementData.MovementComponent->Mobility = EComponentMobility::Type::Movable;
		ComponentMovementData.DestinationTransform = ComponentMovementData.MovementComponent->GetRelativeTransform() + DestinationDeltaTransform;
		ComponentMovementData.DestinationTransform.SetRotation((ComponentMovementData.MovementComponent->GetRelativeRotation() + DestinationDeltaTransform.Rotator()).Quaternion());
	}
}

void UComponentMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (FComponentMovementData& ComponentMovementData : ComponentMovementDatas)
	{
		if (ComponentMovementData.MovementComponent.IsValid())
		{
			if (bIsOnTrigger)
			{
				FTransform Source = ComponentMovementData.MovementComponent->GetRelativeTransform();
			
				if (bIsUpdateScale)
				{
					ComponentMovementData.MovementComponent->SetRelativeScale3D(FMath::VInterpTo(Source.GetScale3D(), ComponentMovementData.DestinationTransform.GetScale3D(), DeltaTime, InterpSpeed));
				}
			
				if (bIsUpdateRotator)
				{
					ComponentMovementData.MovementComponent->SetRelativeRotation(FQuat::FastLerp(Source.GetRotation(), Source.GetRotation() + ComponentMovementData.DestinationTransform.GetRotation(), DeltaTime * InterpSpeed));
				}
			
				if (bIsUpdateLocation)
				{
					ComponentMovementData.MovementComponent->SetRelativeLocation(FMath::VInterpTo(Source.GetLocation(), ComponentMovementData.DestinationTransform.GetLocation(), DeltaTime, InterpSpeed));
				}
			}
			else
			{
				FTransform Source = ComponentMovementData.MovementComponent->GetRelativeTransform();
			
				if (bIsUpdateScale)
				{
					ComponentMovementData.MovementComponent->SetRelativeScale3D(FMath::VInterpTo(Source.GetScale3D(), ComponentMovementData.SourceTransform.GetScale3D(), DeltaTime, InterpSpeed));
				}
			
				if (bIsUpdateRotator)
				{
					ComponentMovementData.MovementComponent->SetRelativeRotation(FQuat::FastLerp(Source.GetRotation(), ComponentMovementData.SourceTransform.GetRotation(), DeltaTime * InterpSpeed));
				}
			
				if (bIsUpdateScale)
				{
					ComponentMovementData.MovementComponent->SetRelativeLocation(FMath::VInterpTo(Source.GetLocation(), ComponentMovementData.SourceTransform.GetLocation(), DeltaTime, InterpSpeed));
				}
			}
		}
	}

}