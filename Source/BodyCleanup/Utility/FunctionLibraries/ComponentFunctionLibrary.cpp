// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentFunctionLibrary.h"
#include "../../Components/Interactive/Interfaces/InteractiveComponentInterface.h"
#include "LevelDesignerTools/Markup/Interfaces/LevelMarkupInterface.h"
#include "../../Components/Interactive/Interfaces/InteractiveComponentInterface.h"
#include "LevelDesignerTools/Trigger/Interfaces/LevelTriggerInterface.h"
#include "../../Components/Interactive/Classes/InteractiveAbilityComponent.h"
#include "../../Components/Interactive/Classes/InteractiveActorComponent.h"
#include "../../Components/Interactive/Classes/InteractiveScriptComponent.h"
#include "../../Components/Interactive/Classes/InteractiveSuckingComponent.h"
#include "../../Components/Interactive/Interfaces/InteractiveComponentInterface.h"

void UComponentFunctionLibrary::FindInteractiveComponents(
	TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, USceneComponent* SceneComponent)
{	
	if (SceneComponent->GetClass()->ImplementsInterface(UInteractiveComponentInterface::StaticClass()))
	{
		InputInteractiveComponents.Add(SceneComponent);
	}
	
	TArray<USceneComponent*> ChildrenComponents;
	SceneComponent->GetChildrenComponents(false, ChildrenComponents);
	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindInteractiveComponents(InputInteractiveComponents, ChildComponent);
	}
}

void UComponentFunctionLibrary::FindInteractiveComponents(
	TArray<UActorComponent*>& InputInteractiveComponents, AActor* Actor)
{
	InputInteractiveComponents = Actor->GetComponentsByInterface(UInteractiveComponentInterface::StaticClass());
}

TSoftObjectPtr<UInteractiveSuckingComponent> UComponentFunctionLibrary::FindInteractiveSuckingComponent(AActor* Actor)
{
	TArray<UActorComponent*> InteractiveComponents;

	FindInteractiveComponents(InteractiveComponents, Actor);

	for(UActorComponent* InteractiveComponent : InteractiveComponents)
	{
		if(InteractiveComponent->IsA(UInteractiveSuckingComponent::StaticClass()))
		{
			return Cast<UInteractiveSuckingComponent>(InteractiveComponent);
		}
	}

	return nullptr;
}