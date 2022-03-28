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
	SetComponentTickEnabled(false);
	TriggerDeltaTime = 0.f;
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

void UComponentMovementComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	SetComponentTickEnabled(true);

	if (TriggerDeltaTime > 0.f)
	{
		TriggerDeltaTime = 1.f - TriggerDeltaTime;
	}
}

void UComponentMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TriggerDeltaTime += DeltaTime * InterpSpeed;

	TriggerDeltaTime = FMath::Clamp(TriggerDeltaTime, 0.f, 1.f);

	for (FComponentMovementData& ComponentMovementData : ComponentMovementDatas)
	{
		if (ComponentMovementData.MovementComponent.IsValid())
		{
			if (IsOnTrigger())
			{
				ComponentMovementData.MovementComponent->SetRelativeScale3D(FMath::Lerp(ComponentMovementData.SourceTransform.GetScale3D(), ComponentMovementData.DestinationTransform.GetScale3D(), TriggerDeltaTime));
				ComponentMovementData.MovementComponent->SetRelativeRotation(FMath::Lerp(ComponentMovementData.SourceTransform.GetRotation().Rotator(), ComponentMovementData.DestinationTransform.GetRotation().Rotator(), TriggerDeltaTime));
				ComponentMovementData.MovementComponent->SetRelativeLocation(FMath::Lerp(ComponentMovementData.SourceTransform.GetLocation(), ComponentMovementData.DestinationTransform.GetLocation(), TriggerDeltaTime));
			}
			else
			{
				ComponentMovementData.MovementComponent->SetRelativeScale3D(FMath::Lerp(ComponentMovementData.DestinationTransform.GetScale3D(), ComponentMovementData.SourceTransform.GetScale3D(), TriggerDeltaTime));
				ComponentMovementData.MovementComponent->SetRelativeRotation(FMath::Lerp(ComponentMovementData.DestinationTransform.GetRotation().Rotator(), ComponentMovementData.SourceTransform.GetRotation().Rotator(), TriggerDeltaTime));
				ComponentMovementData.MovementComponent->SetRelativeLocation(FMath::Lerp(ComponentMovementData.DestinationTransform.GetLocation(), ComponentMovementData.SourceTransform.GetLocation(), TriggerDeltaTime));
			}
		}
	}

	if (TriggerDeltaTime >= 1.f)
	{
		TriggerDeltaTime = 0.f;
		SetComponentTickEnabled(false);
	}
}