// Fill out your copyright notice in the Description page of Project Settings.


#include "FindFunctionLibrary.h"
#include "../../Components/Interfaces/InteractiveInterface.h"
#include "../../Components/Interfaces/LevelActionInterface.h"
#include "LevelDesignerTools/Markup/Interfaces/LevelMarkupInterface.h"
//#include "../../Components/Interfaces/LevelTriggerInterface.h"
#include "LevelDesignerTools/Trigger/Interfaces/LevelTriggerInterface.h"

void UFindFunctionLibrary::FindComponentByClass(TArray<TSoftObjectPtr<UActorComponent>>& Components, USceneComponent* SceneComponent, UClass* Class)
{
	if (SceneComponent->IsA(Class))
	{
		Components.Add(SceneComponent);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindComponentByClass(Components, ChildComponent, Class);
	}
}

void UFindFunctionLibrary::FindPrimitiveComponets(TArray<TSoftObjectPtr<UPrimitiveComponent>>& Components, USceneComponent* SceneComponent)
{
	if (SceneComponent->IsA(UPrimitiveComponent::StaticClass()))
	{
		Components.Add(Cast<UPrimitiveComponent>(SceneComponent));
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindPrimitiveComponets(Components, ChildComponent);
	}	
}

USceneComponent* UFindFunctionLibrary::FindComponentByName(USceneComponent* SceneComponent, const FName& Name)
{
	if (SceneComponent->GetName() == Name.ToString())
	{
		return SceneComponent;
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		USceneComponent* FindComponent = FindComponentByName(ChildComponent, Name);

		if (IsValid(FindComponent))
		{
			return FindComponent;
		}
	}

	return nullptr;
}

void UFindFunctionLibrary::FindComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& NameComponents, USceneComponent* SceneComponent, const TArray<FName>& Names)
{
	if (Names.Find(FName(SceneComponent->GetName())) >= 0)
	{
		NameComponents.Add(SceneComponent);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindComponentsByNames(NameComponents, ChildComponent, Names);
	}
}

void UFindFunctionLibrary::FindComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& TagComponents, AActor* Actor, const FName& TagName)
{
	TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(USceneComponent::StaticClass(), TagName);

	for (UActorComponent* TriggerComponent : ActorTriggerComponents)
	{
		TagComponents.Add(TriggerComponent);
	}
}

void UFindFunctionLibrary::FindComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& TagComponents, AActor* Actor, const TArray<FName>& TagNames)
{
	for (const FName& TagName : TagNames)
	{
		TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(USceneComponent::StaticClass(), TagName);

		for (UActorComponent* TriggerComponent : ActorTriggerComponents)
		{
			TagComponents.Add(TriggerComponent);
		}
	}
}

UPrimitiveComponent* UFindFunctionLibrary::FindPrimitiveComponentByName(USceneComponent* SceneComponent, const FName& Name)
{
	if (SceneComponent->GetName() == Name.ToString())
	{
		return Cast<UPrimitiveComponent>(SceneComponent);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		UPrimitiveComponent* FindComponent = FindPrimitiveComponentByName(ChildComponent, Name);

		if (IsValid(FindComponent))
		{
			return FindComponent;
		}
	}

	return nullptr;
}

void UFindFunctionLibrary::FindPrimitiveComponentsByNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& NameComponents, USceneComponent* SceneComponent, const TArray<FName>& Names)
{
	if (Names.Find(FName(SceneComponent->GetName())) >= 0)
	{
		if (SceneComponent->IsA(UPrimitiveComponent::StaticClass()))
		{
			NameComponents.Add(SceneComponent);
		}
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindPrimitiveComponentsByNames(NameComponents, ChildComponent, Names);
	}
}

void UFindFunctionLibrary::FindPrimitiveComponentsByTagName(TArray<TSoftObjectPtr<UPrimitiveComponent>>& TagComponents, AActor* Actor, const FName& TagName)
{
	TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(UPrimitiveComponent::StaticClass(), TagName);

	for (UActorComponent* TriggerComponent : ActorTriggerComponents)
	{
		TagComponents.Add(TriggerComponent);
	}
}

void UFindFunctionLibrary::FindPrimitiveComponentsByTagNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& TagComponents, AActor* Actor, const TArray<FName>& TagNames)
{
	for (const FName& TagName : TagNames)
	{
		TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(UPrimitiveComponent::StaticClass(), TagName);

		for (UActorComponent* TriggerComponent : ActorTriggerComponents)
		{
			TagComponents.Add(TriggerComponent);
		}
	}
}

USceneComponent* UFindFunctionLibrary::FindTriggerComponentByName(USceneComponent* SceneComponent, const FName& Name)
{
	if (SceneComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
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
		USceneComponent* FindTriggerComponent = FindTriggerComponentByName(ChildComponent, Name);

		if (IsValid(FindTriggerComponent))
		{
			return FindTriggerComponent;
		}
	}

	return nullptr;
}

void UFindFunctionLibrary::FindTriggerComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents, USceneComponent* SceneComponent)
{
	if (SceneComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
	{
		InputTriggerComponents.Add(SceneComponent);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindTriggerComponents(InputTriggerComponents, ChildComponent);
	}
}

void UFindFunctionLibrary::FindTriggerComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents, AActor* Actor, const FName& TagName)
{
	TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(ULevelTriggerInterface::StaticClass(), TagName);

	for (UActorComponent* TriggerComponent : ActorTriggerComponents)
	{
		InputTriggerComponents.Add(TriggerComponent);
	}
}

USceneComponent* UFindFunctionLibrary::FindMarkupComponentByName(USceneComponent* SceneComponent, const FName& Name)
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

void UFindFunctionLibrary::FindMarkupComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, USceneComponent* SceneComponent, const TArray<FName>& Names)
{
	if (SceneComponent->GetClass()->ImplementsInterface(ULevelMarkupInterface::StaticClass()))
	{
		if (Names.Find(FName(SceneComponent->GetName())) >= 0)
		{
			InputMarkupComponents.Add(SceneComponent);
		}
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindMarkupComponentsByNames(InputMarkupComponents, ChildComponent, Names);
	}
}

void UFindFunctionLibrary::FindMarkupComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, AActor* Actor, const FName& TagName)
{
	TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(ULevelMarkupInterface::StaticClass(), TagName);

	for (UActorComponent* TriggerComponent : ActorTriggerComponents)
	{
		InputMarkupComponents.Add(TriggerComponent);
	}
}

void UFindFunctionLibrary::FindMarkupComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, AActor* Actor, const TArray<FName>& TagNames)
{
	for (const FName& TagName : TagNames)
	{
		TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(ULevelMarkupInterface::StaticClass(), TagName);

		for (UActorComponent* TriggerComponent : ActorTriggerComponents)
		{
			InputMarkupComponents.Add(TriggerComponent);
		}
	}
}

void UFindFunctionLibrary::FindInteractiveComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, USceneComponent* SceneComponent)
{
	if (SceneComponent->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
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

USceneComponent* UFindFunctionLibrary::FindInteractiveComponentByName(USceneComponent* SceneComponent, const FName& Name)
{
	if (SceneComponent->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
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

void UFindFunctionLibrary::FindInteractiveComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, USceneComponent* SceneComponent, const TArray<FName>& Names)
{
	if (SceneComponent->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
	{
		if (Names.Find(FName(SceneComponent->GetName())) >= 0)
		{
			InputInteractiveComponents.Add(SceneComponent);
		}
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindInteractiveComponentsByNames(InputInteractiveComponents, ChildComponent, Names);
	}
}

void UFindFunctionLibrary::FindInteractiveComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, AActor* Actor, const FName& TagName)
{
	TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(UInteractiveInterface::StaticClass(), TagName);

	for (UActorComponent* TriggerComponent : ActorTriggerComponents)
	{
		InputInteractiveComponents.Add(TriggerComponent);
	}
}

void UFindFunctionLibrary::FindInteractiveComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, AActor* Actor, const TArray<FName>& TagNames)
{
	for (const FName& TagName : TagNames)
	{
		TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(UInteractiveInterface::StaticClass(), TagName);

		for (UActorComponent* TriggerComponent : ActorTriggerComponents)
		{
			InputInteractiveComponents.Add(TriggerComponent);
		}
	}
}
