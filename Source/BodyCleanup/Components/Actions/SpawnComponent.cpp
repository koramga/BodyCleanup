// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include "../Interfaces/LevelMarkupInterface.h"

void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ESpawnComponentType::Hidden == SpawnComponentType)
	{
		for (FHiddenParam& HiddenParam : HiddenParams)
		{
			if (HiddenParam.Actor.IsValid())
			{
				HiddenParam.Transform = HiddenParam.Actor->GetTransform();
				HiddenParam.Actor->SetActorEnableCollision(false);
				HiddenParam.Actor->SetActorTickEnabled(false);
				HiddenParam.Actor->SetActorHiddenInGame(true);
			}
		}
	}
}

void USpawnComponent::OnTrigger(bool bInputIsOnTrigger)
{
	if (bInputIsOnTrigger)
	{
		if (ESpawnComponentType::Hidden == SpawnComponentType)
		{
			for (const FHiddenParam& HiddenParam : HiddenParams)
			{
				HiddenParam.Actor->SetActorEnableCollision(true);
				HiddenParam.Actor->SetActorTickEnabled(true);
				HiddenParam.Actor->SetActorHiddenInGame(false);
				HiddenParam.Actor->SetActorTransform(HiddenParam.Transform);
			}
		}
		else if (ESpawnComponentType::Spawn == SpawnComponentType)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Owner = GetOwner();

			for (FSpawnMarkupParam& SpawnMarkupParam : SpawnMarkupParams)
			{
				if (IsValid(SpawnMarkupParam.ActorClass.Get()))
				{
					TArray<FTransform> Transforms;

					SpawnInfo.SpawnCollisionHandlingOverride = SpawnMarkupParam.SpawnMethod;

					GetTransformsFromSpawnMarkupParam(Transforms, SpawnMarkupParam);

					for (const FTransform& Transform : Transforms)
					{
						GetWorld()->SpawnActor<AActor>(SpawnMarkupParam.ActorClass, Transform.GetLocation(), Transform.GetRotation().Rotator(), SpawnInfo);
					}
				}
			}
		}
	}
}

void USpawnComponent::GetTransformsFromSpawnMarkupParam(TArray<FTransform>& Transforms, const FSpawnMarkupParam& SpawnMarkupParam)
{
	TSoftObjectPtr<AActor> Actor = GetOwner();

	if (SpawnMarkupParam.Actor.IsValid())
	{
		Actor = SpawnMarkupParam.Actor;
	}

	if (SpawnMarkupParam.Names.Num() > 0)
	{
		TArray<TSoftObjectPtr<USceneComponent>> MarkupComponents;

		if (ENameType::Name == SpawnMarkupParam.NameType)
		{
			FindMarkupComponentsByNames(MarkupComponents, Actor->GetRootComponent(), SpawnMarkupParam.Names);
		}
		else if (ENameType::Tag == SpawnMarkupParam.NameType)
		{
			FindMarkupComponentsByTagNames(MarkupComponents, Actor.Get(), SpawnMarkupParam.Names);
		}

		for (TSoftObjectPtr<USceneComponent> MarkupComponent : MarkupComponents)
		{
			ILevelMarkupInterface* LevelMarkupInterface = Cast<ILevelMarkupInterface>(MarkupComponent.Get());

			if (nullptr != LevelMarkupInterface)
			{
				Transforms.Add(LevelMarkupInterface->GetMarkupTransform());
			}
		}
	}
	else
	{
		if (GetOwner() == Actor)
		{
			Transforms.Add(GetComponentToWorld());
		}
		else
		{
			Transforms.Add(Actor->GetTransform());
		}
	}
}

void USpawnComponent::GetAffectPoints(TArray<FVector>& Locations)
{
	if (ESpawnComponentType::Hidden == SpawnComponentType)
	{
		for (const FHiddenParam& HiddenParam : HiddenParams)
		{
			if (HiddenParam.Actor.IsValid())
			{
				Locations.Add(HiddenParam.Actor->GetActorLocation());
			}
		}
	}
	else if (ESpawnComponentType::Spawn == SpawnComponentType)
	{
		for (const FSpawnMarkupParam& SpawnMarkupParam : SpawnMarkupParams)
		{
			if (IsValid(SpawnMarkupParam.ActorClass.Get()))
			{
				TArray<FTransform> Transforms;

				GetTransformsFromSpawnMarkupParam(Transforms, SpawnMarkupParam);

				for (const FTransform& Transform : Transforms)
				{
					Locations.Add(Transform.GetLocation());
				}
			}
		}
	}
}
