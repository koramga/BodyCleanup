// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include "LevelDesignerTools/Markup/Interfaces/LevelMarkupInterface.h"
#include "../../Utilities/FunctionLibraries/FindFunctionLibrary.h"
#include "../Markups/VelocityMarkupComponent.h"

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
					TArray<TSoftObjectPtr<UObject>> Objects;

					SpawnInfo.SpawnCollisionHandlingOverride = SpawnMarkupParam.SpawnMethod;

					GetActorsFromSpawnMarkupParam(Objects, SpawnMarkupParam);

					for (TSoftObjectPtr<UObject> Object : Objects)
					{
						if (Object->GetClass()->ImplementsInterface(ULevelMarkupInterface::StaticClass()))
						{
							ILevelMarkupInterface* LevelMarkupInterface = Cast<ILevelMarkupInterface>(Object.Get());

							const FTransform& Transform = LevelMarkupInterface->GetMarkupTransform();

							AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(SpawnMarkupParam.ActorClass, Transform.GetLocation(), Transform.GetRotation().Rotator(), SpawnInfo);

							LevelMarkupInterface->UpdateFromMarkup(SpawnActor);
						}
						else if (Object->IsA(AActor::StaticClass()))
						{
							AActor* Actor = Cast<AActor>(Object.Get());

							GetWorld()->SpawnActor<AActor>(SpawnMarkupParam.ActorClass, Actor->GetActorLocation(), Actor->GetActorRotation(), SpawnInfo);
						}
						else if (Object->IsA(USceneComponent::StaticClass()))
						{
							USceneComponent* SceneComponenet = Cast<USceneComponent>(Object.Get());

							const FTransform& Transform = SceneComponenet->GetComponentToWorld();

							GetWorld()->SpawnActor<AActor>(SpawnMarkupParam.ActorClass, Transform.GetLocation(), Transform.GetRotation().Rotator(), SpawnInfo);
						}
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
			UFindFunctionLibrary::FindMarkupComponentsByNames(MarkupComponents, Actor->GetRootComponent(), SpawnMarkupParam.Names);
		}
		else if (ENameType::Tag == SpawnMarkupParam.NameType)
		{
			UFindFunctionLibrary::FindMarkupComponentsByTagNames(MarkupComponents, Actor.Get(), SpawnMarkupParam.Names);
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

void USpawnComponent::GetActorsFromSpawnMarkupParam(TArray<TSoftObjectPtr<UObject>>& Objects, const FSpawnMarkupParam& SpawnMarkupParam)
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
			UFindFunctionLibrary::FindMarkupComponentsByNames(MarkupComponents, Actor->GetRootComponent(), SpawnMarkupParam.Names);
		}
		else if (ENameType::Tag == SpawnMarkupParam.NameType)
		{
			UFindFunctionLibrary::FindMarkupComponentsByTagNames(MarkupComponents, Actor.Get(), SpawnMarkupParam.Names);
		}

		for (TSoftObjectPtr<USceneComponent> MarkupComponent : MarkupComponents)
		{
			ILevelMarkupInterface* LevelMarkupInterface = Cast<ILevelMarkupInterface>(MarkupComponent.Get());

			if (nullptr != LevelMarkupInterface)
			{
				Objects.Add(MarkupComponent);
			}
		}
	}
	else
	{
		if (GetOwner() == Actor)
		{
			Objects.Add(this);
		}
		else
		{
			Objects.Add(Actor);
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
