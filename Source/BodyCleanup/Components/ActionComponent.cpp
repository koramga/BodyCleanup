// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Interfaces/LevelMarkupInterface.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActionComponent::OnTrigger(bool bInputIsOnTrigger)
{
	bIsUpdateDestinationTransformed = bInputIsOnTrigger;
}

void UActionComponent::UpdateTrigger(bool bInputIsOnTrigger)
{
	Super::UpdateTrigger(bInputIsOnTrigger);

	if (EActionComponentActionType::On == ActionType)
	{
		if (false == bIsUpdateDestinationTransformed)
		{
			if (true == bInputIsOnTrigger)
			{
				OnTrigger(bInputIsOnTrigger);
			}
		}
	}
	else
	{
		OnTrigger(bIsOnTrigger);
	}	
}

USceneComponent* UActionComponent::FindMarkupComponentByName(USceneComponent* SceneComponent, const FName& Name) const
{
	if (SceneComponent->GetClass()->ImplementsInterface(ULevelMarkupInterface::StaticClass()))
	{
		if (SceneComponent->GetName() == Name.ToString())
		{
			return SceneComponent;
		}
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		USceneComponent* FindTriggerComponent = FindMarkupComponentByName(ChildComponent, Name);

		if (IsValid(FindTriggerComponent))
		{
			return FindTriggerComponent;
		}
	}

	return nullptr;
}

void UActionComponent::FindMarkupComponentByTagName(TArray<TSoftObjectPtr<UActorComponent>>& InputMarkupComponents, AActor* Actor, const FName& TagName) const
{
	TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(ULevelMarkupInterface::StaticClass(), TagName);

	for (UActorComponent* TriggerComponent : ActorTriggerComponents)
	{
		InputMarkupComponents.Add(TriggerComponent);
	}
}

bool UActionComponent::IsUpdateDestinationTransformed() const
{
	return bIsUpdateDestinationTransformed;
}
