// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSupportFunctionLibrary.h"
#include "../Trigger/Interfaces/LevelTriggerInterface.h"
#include "../Markup/Interfaces/LevelMarkupInterface.h"

void ULevelSupportFunctionLibrary::FindTriggerComponentFromLevelTriggerInput(TArray<TSoftObjectPtr<UActorComponent>>& TriggerComponents, const ILevelTriggerInterface* LevelTriggerInterface)
{
	const FLevelTriggerInput* LevelTriggerInput = LevelTriggerInterface->GetLevelTriggerInput();

	const UActorComponent* LevelActorTriggerComponent = Cast<UActorComponent>(LevelTriggerInterface);

	if (IsValid(LevelActorTriggerComponent))
	{
		const USceneComponent* LevelSceneTriggerComponent = Cast<USceneComponent>(LevelTriggerInterface);
		AActor* Owner = LevelActorTriggerComponent->GetOwner();

		if (ELevelTriggerInputNodeType::Parent == LevelTriggerInput->LevelTriggerInputNodeType)
		{
			if (IsValid(LevelSceneTriggerComponent))
			{
				TriggerComponents.Add(LevelSceneTriggerComponent->GetAttachParent());
			}

		}
		else if (ELevelTriggerInputNodeType::Setup == LevelTriggerInput->LevelTriggerInputNodeType)
		{
			for (const FLevelTriggerInputNode& TriggerInputNode : LevelTriggerInput->LevelTriggerInputNodes)
			{
				TSoftObjectPtr<AActor> TriggerActor = Owner;

				if (TriggerInputNode.Actor.IsValid())
				{
					TriggerActor = TriggerInputNode.Actor;
				}

				if (TriggerActor.IsValid())
				{
					if (TriggerInputNode.Names.Num() > 0)
					{
						if (false == TriggerInputNode.bIsTag)
						{
							for (const FName& Name : TriggerInputNode.Names)
							{
								UActorComponent* FindActorComponent = Cast<UActorComponent>(TriggerActor->GetDefaultSubobjectByName(Name));

								if (IsValid(FindActorComponent))
								{
									TriggerComponents.Add(FindActorComponent);
								}
							}
						}
						else
						{
							for (const FName& Name : TriggerInputNode.Names)
							{
								TArray<UActorComponent*> ActorComponents = TriggerActor->GetComponentsByTag(USceneComponent::StaticClass(), Name);

								for (UActorComponent* ActorComponent : ActorComponents)
								{
									TriggerComponents.Add(ActorComponent);
								}
							}
						}
					}
					else
					{
						TArray<TSoftObjectPtr<ILevelTriggerInterface>> LevelTriggerInterfaces;

						FindTriggerInterfaces(LevelTriggerInterfaces, TriggerActor.Get());

						for (const TSoftObjectPtr<ILevelTriggerInterface>& ParamLevelTriggerInterface : LevelTriggerInterfaces)
						{
							UActorComponent* ActorComponent = Cast<UActorComponent>(ParamLevelTriggerInterface.Get());

							if (IsValid(ActorComponent))
							{
								TriggerComponents.Add(ActorComponent);
							}
						}
					}
				}
			}
		}
	}


	//InputTriggerComponents.Empty();
	//
	//TArray<TSoftObjectPtr<USceneComponent>> FindComponents;
	//
	//if (ETriggerComponentFromType::Parent == TriggerComponentFromType)
	//{
	//	FindComponents.Add(GetAttachParent());
	//}
	//else if (ETriggerComponentFromType::Setup == TriggerComponentFromType)
	//{
	//	for (const FTriggerActorWithName& TriggerActorWithName : TriggerActorWithNames)
	//	{
	//		TSoftObjectPtr<AActor> TriggerActor = GetOwner();
	//
	//		if (TriggerActorWithName.Actor.IsValid())
	//		{
	//			TriggerActor = TriggerActorWithName.Actor;
	//		}
	//
	//		if (TriggerActor.IsValid())
	//		{
	//			if (TriggerActorWithName.Names.Num() > 0)
	//			{
	//				if (ENameType::Name == TriggerActorWithName.NameType)
	//				{
	//					UFindFunctionLibrary::FindComponentsByNames(FindComponents, TriggerActor->GetRootComponent(), TriggerActorWithName.Names);
	//				}
	//				else
	//				{
	//					for (const FName& Name : TriggerActorWithName.Names)
	//					{
	//						TArray<UActorComponent*> ActorComponents = TriggerActor->GetComponentsByTag(USceneComponent::StaticClass(), Name);
	//
	//						for (UActorComponent* ActorComponent : ActorComponents)
	//						{
	//							USceneComponent* SceneComponent = Cast<USceneComponent>(ActorComponent);
	//
	//							if (IsValid(SceneComponent))
	//							{
	//								FindComponents.Add(SceneComponent);
	//							}
	//						}
	//					}
	//				}
	//			}
	//			else
	//			{
	//				UFindFunctionLibrary::FindTriggerComponents(FindComponents, TriggerActor->GetRootComponent());
	//			}
	//		}
	//	}
	//}
}

void ULevelSupportFunctionLibrary::FindPrimitiveComponets(TArray<TSoftObjectPtr<UPrimitiveComponent>>& Components, AActor* Actor)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByClass(UPrimitiveComponent::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		Components.Add(TriggerComponent);
	}
}

UPrimitiveComponent* ULevelSupportFunctionLibrary::FindPrimitiveComponentByName(AActor* Actor, const FName& Name)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByClass(UPrimitiveComponent::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->GetName() == Name.ToString())
		{
			return Cast<UPrimitiveComponent>(TriggerComponent);
		}
	}

	return nullptr;
}

void ULevelSupportFunctionLibrary::FindPrimitiveComponentsByNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& PrimitiveComponents, AActor* Actor, const TArray<FName>& Names)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByClass(UPrimitiveComponent::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (Names.Find(FName(TriggerComponent->GetName())) >= 0)
		{
			PrimitiveComponents.Add(TriggerComponent);
		}
	}
}

void ULevelSupportFunctionLibrary::FindPrimitiveComponentsByTag(TArray<TSoftObjectPtr<UPrimitiveComponent>>& PrimitiveComponents, AActor* Actor, const FName& Tag)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByClass(UPrimitiveComponent::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->ComponentHasTag(Tag))
		{
			PrimitiveComponents.Add(TriggerComponent);
		}
	}
}

void ULevelSupportFunctionLibrary::FindPrimitiveComponentsByTags(TArray<TSoftObjectPtr<UPrimitiveComponent>>& PrimitiveComponents, AActor* Actor, const TArray<FName>& Tags)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByClass(UPrimitiveComponent::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		for (const FName& Tag : Tags)
		{
			if (TriggerComponent->ComponentHasTag(Tag))
			{
				PrimitiveComponents.Add(TriggerComponent);
				break;
			}
		}
	}
}

void ULevelSupportFunctionLibrary::FindTriggerInterfaces(TArray<TSoftObjectPtr<ILevelTriggerInterface>>& InputTriggerComponents, AActor* Actor)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelTriggerInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		InputTriggerComponents.Add(TriggerComponent);
	}
}

ILevelTriggerInterface* ULevelSupportFunctionLibrary::FindTriggerInterfaceByName(AActor* Actor, const FName& Name)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelTriggerInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->GetName() == Name.ToString())
		{
			return Cast<ILevelTriggerInterface>(TriggerComponent);
		}
	}

	return nullptr;
}

void ULevelSupportFunctionLibrary::FindTriggerInterfacesByNames(TArray<TSoftObjectPtr<ILevelTriggerInterface>> &InputTriggerComponents, AActor* Actor, const TArray<FName>& Names)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelTriggerInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (Names.Find(FName(TriggerComponent->GetName())) >= 0)
		{
			InputTriggerComponents.Add(TriggerComponent);
		}
	}
}

void ULevelSupportFunctionLibrary::FindTriggerInterfacesByTag(TArray<TSoftObjectPtr<ILevelTriggerInterface>>& InputTriggerComponents, AActor* Actor, const FName& Tag)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelTriggerInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->ComponentHasTag(Tag))
		{
			InputTriggerComponents.Add(TriggerComponent);
		}
	}
}

void ULevelSupportFunctionLibrary::FindTriggerInterfacesByTags(TArray<TSoftObjectPtr<ILevelTriggerInterface>>& InputTriggerComponents, AActor* Actor, const TArray<FName>& Tags)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelTriggerInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		for (const FName& Tag : Tags)
		{
			if (TriggerComponent->ComponentHasTag(Tag))
			{
				InputTriggerComponents.Add(TriggerComponent);
				break;
			}
		}
	}
}

void ULevelSupportFunctionLibrary::FindMarkupInterfaces(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputMarkupInterfaces, AActor* Actor)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelMarkupInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		InputMarkupInterfaces.Add(TriggerComponent);
	}
}

ILevelMarkupInterface* ULevelSupportFunctionLibrary::FindMarkupInterfaceByName(AActor* Actor, const FName& Name)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelMarkupInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->GetName() == Name.ToString())
		{
			return Cast<ILevelMarkupInterface>(TriggerComponent);
		}
	}

	return nullptr;
}

void ULevelSupportFunctionLibrary::FindMarkupInterfacesByNames(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputMarkupInterfaces, AActor* Actor, const TArray<FName>& Names)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelMarkupInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (Names.Find(FName(TriggerComponent->GetName())) >= 0)
		{
			InputMarkupInterfaces.Add(TriggerComponent);
		}
	}
}

void ULevelSupportFunctionLibrary::FindMarkupInterfacesByTag(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputMarkupInterfaces, AActor* Actor, const FName& Tag)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelMarkupInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->ComponentHasTag(Tag))
		{
			InputMarkupInterfaces.Add(TriggerComponent);
		}
	}
}

void ULevelSupportFunctionLibrary::FindMarkupInterfacesByTags(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputMarkupInterfaces, AActor* Actor, const TArray<FName>& Tags)
{
	TArray<UActorComponent*> TriggerComponents = Actor->GetComponentsByInterface(ULevelMarkupInterface::StaticClass());

	for (UActorComponent* TriggerComponent : TriggerComponents)
	{
		for (const FName& Tag : Tags)
		{
			if (TriggerComponent->ComponentHasTag(Tag))
			{
				InputMarkupInterfaces.Add(TriggerComponent);
				break;
			}
		}
	}
}
