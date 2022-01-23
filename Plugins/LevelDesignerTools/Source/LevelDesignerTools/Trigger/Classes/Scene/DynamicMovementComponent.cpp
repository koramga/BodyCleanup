// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMovementComponent.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"

UDynamicMovementComponent::UDynamicMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDynamicMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
}

void UDynamicMovementComponent::SetupTrigger()
{
	Super::SetupTrigger();

	if (ELevelTriggerInputNodeToType::Parent == LevelTriggerInputTo.LevelTriggerInputNodeToType)
	{
		USceneComponent* AttachParentComponent = GetAttachParent();

		if (IsValid(AttachParentComponent))
		{
			DynamicMovementParams.Add(FDynamicMovementParam(AttachParentComponent));
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
					DynamicMovementParams.Add(FDynamicMovementParam(SceneComponent));
				}
			}
		}
	}

	for (FDynamicMovementParam& DynamicMovementParam : DynamicMovementParams)
	{
		DynamicMovementParam.MovementComponent->Mobility = EComponentMobility::Type::Movable;

		for (const FTransform& DestinationDeltaTransform : DestinationDeltaTransforms)
		{
			FTransform InputTransform = DynamicMovementParam.Transforms[DynamicMovementParam.Transforms.Num() - 1];

			InputTransform.SetRotation((InputTransform.GetRotation() + DestinationDeltaTransform.GetRotation()));
			InputTransform.SetLocation(InputTransform.GetLocation() + DestinationDeltaTransform.GetLocation());
			InputTransform.SetScale3D(InputTransform.GetScale3D() + DestinationDeltaTransform.GetScale3D());

			DynamicMovementParam.Transforms.Add(InputTransform); 
		}

		SourceTransforms.Add(FTransform());
		DestTransforms.Add(FTransform());
	}
}

void UDynamicMovementComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (InputLevelTriggerUpdateParam.bIsOnTriggers[DEFAULT_TRIGGER_INDEX])
	{
		if (EDynamicMovementCycleType::Cycle == DynamicMovementCycleType)
		{
			ComponentMovementIndex = (ComponentMovementIndex + 1) % (DestinationDeltaTransforms.Num() + 1);
		}
		else
		{
			if (ReverseSign > 0)
			{
				if (DestinationDeltaTransforms.Num() + 1 <= ComponentMovementIndex + 1)
				{
					ReverseSign *= -1;
				}
			}
			else if (ReverseSign < 0)
			{
				if (ComponentMovementIndex - 1 < 0)
				{
					ReverseSign *= -1;
				}
			}

			ComponentMovementIndex += ReverseSign;
		}

		
		for (int DynamicMovementParamIndex = 0; DynamicMovementParamIndex < DynamicMovementParams.Num(); ++DynamicMovementParamIndex)
		{
			const FDynamicMovementParam& DynamicMovementParam = DynamicMovementParams[DynamicMovementParamIndex];

			SourceTransforms[DynamicMovementParamIndex] = DynamicMovementParam.MovementComponent->GetRelativeTransform();
			DestTransforms[DynamicMovementParamIndex] = DynamicMovementParam.Transforms[ComponentMovementIndex];
		}

		TriggerDeltaTime = 0.f;

		SetComponentTickEnabled(true);
	}
}

void UDynamicMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TriggerDeltaTime += DeltaTime * InterpSpeed;

	if (TriggerDeltaTime >= 1.f)
	{
		TriggerDeltaTime = 1.f;
		SetComponentTickEnabled(false);
	}

	for (int DynamicMovementParamIndex = 0; DynamicMovementParamIndex < DynamicMovementParams.Num(); ++DynamicMovementParamIndex)
	{
		const FDynamicMovementParam& DynamicMovementParam = DynamicMovementParams[DynamicMovementParamIndex];

		if (DynamicMovementParam.MovementComponent.IsValid())
		{
			FTransform Source = DynamicMovementParam.MovementComponent->GetRelativeTransform();
			const FTransform& DestinationTransform = DynamicMovementParam.Transforms[ComponentMovementIndex];

			DynamicMovementParam.MovementComponent->SetRelativeScale3D(FMath::Lerp(SourceTransforms[DynamicMovementParamIndex].GetScale3D(), DestTransforms[DynamicMovementParamIndex].GetScale3D(), TriggerDeltaTime));
			DynamicMovementParam.MovementComponent->SetRelativeRotation(FMath::Lerp(SourceTransforms[DynamicMovementParamIndex].GetRotation().Rotator(), DestTransforms[DynamicMovementParamIndex].GetRotation().Rotator(), TriggerDeltaTime));
			DynamicMovementParam.MovementComponent->SetRelativeLocation(FMath::Lerp(SourceTransforms[DynamicMovementParamIndex].GetLocation(), DestTransforms[DynamicMovementParamIndex].GetLocation(), TriggerDeltaTime));
		}
	}
}