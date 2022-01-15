// Fill out your copyright notice in the Description page of Project Settings.


#include "WarpComponent.h"
#include "../../Actor/BaseActor.h"
#include "../MarkupComponent.h"
#include "../../Utilities/FunctionLibraries/FindFunctionLibrary.h"

// Sets default values for this component's properties
UWarpComponent::UWarpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWarpComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (EWarpType::Location == WarpType)
	{
		MarkupComponent = FindMarkupComponent();
	}
}

void UWarpComponent::OnTrigger(bool bInputIsOnTrigger)
{
	Super::OnTrigger(bInputIsOnTrigger);

	if (EWarpType::Location == WarpType)
	{
		if (bInputIsOnTrigger)
		{
			//반응하면 됩니다.
			TArray<TSoftObjectPtr<AActor>> Actors;

			FindTriggerOnActors(Actors);

			if (Actors.Num() > 0)
			{
				FVector Location = GetOwner()->GetActorLocation();

				if (WarpActor.IsValid())
				{
					Location = WarpActor->GetActorLocation();
				}

				if (MarkupComponent.IsValid())
				{
					Location = MarkupComponent->GetComponentToWorld().GetLocation();
				}

				for (TSoftObjectPtr<AActor> Actor : Actors)
				{
					Actor->SetActorLocation(Location);
				}
			}
		}
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}

}

EWarpType UWarpComponent::GetWarpType() const
{
	return WarpType;
}

TSoftObjectPtr<USceneComponent> UWarpComponent::GetMarkupComponent() const
{
	return MarkupComponent;
}

TSoftObjectPtr<AActor> UWarpComponent::GetWarpActor() const
{
	return WarpActor;
}

TSoftObjectPtr<USceneComponent> UWarpComponent::FindMarkupComponent() const
{
	if (false == MarkupName.IsNone())
	{
		if (EWarpType::Location == WarpType)
		{
			if (WarpActor.IsValid())
			{
				if (false == MarkupName.IsNone())
				{
					return UFindFunctionLibrary::FindMarkupComponentByName(WarpActor->GetRootComponent(), MarkupName);
				}
			}
			else
			{
				return UFindFunctionLibrary::FindMarkupComponentByName(GetOwner()->GetRootComponent(), MarkupName);
			}
		}
	}

	return nullptr;
}

FVector UWarpComponent::GetWarpLocation() const
{
	AActor* StdActor = GetOwner();

	if (WarpActor.IsValid())
	{
		StdActor = WarpActor.Get();
	}

	if (false == MarkupName.IsNone())
	{
		TSoftObjectPtr<USceneComponent> FindComponent = FindMarkupComponent();

		if (FindComponent.IsValid())
		{
			return FindComponent->GetComponentTransform().GetLocation();
		}		
	}

	return StdActor->GetActorLocation();
}