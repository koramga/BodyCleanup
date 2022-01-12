// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	__GetTriggerComponents(TriggerComponents);

	if (ETriggerComponentFromType::ParentComponent == TriggerComponentFromType
		|| ETriggerComponentFromType::ComponentTagName == TriggerComponentFromType
		|| ETriggerComponentFromType::ComponentName == TriggerComponentFromType)
	{
		for (TSoftObjectPtr<UActorComponent> TriggerComponent : TriggerComponents)
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(TriggerComponent.Get());

			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapBegin);
			PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapEnd);
		}
	}
	else
	{
		for (TSoftObjectPtr<UActorComponent> TriggerComponent : TriggerComponents)
		{
			Cast<ILevelTriggerInterface>(TriggerComponent.Get())->AddTriggerObserver(this);
		}
	}
}



USceneComponent* UTriggerComponent::FindComponentByName(USceneComponent* SceneComponent, const FName& Name)
{
	if (SceneComponent->GetName() == Name.ToString())
	{
		return SceneComponent;
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		return FindComponentByName(ChildComponent, Name);
	}

	return nullptr;
}

void UTriggerComponent::FindTriggerComponent(TArray<TSoftObjectPtr<UActorComponent>>& InputTriggerComponents, USceneComponent* SceneComponent)
{
	if (SceneComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
	{
		InputTriggerComponents.Add(SceneComponent);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		FindTriggerComponent(InputTriggerComponents, ChildComponent);
	}
}

void UTriggerComponent::FindTriggerComponentByTagName(TArray<TSoftObjectPtr<UActorComponent>>& InputTriggerComponents, AActor* Actor, const FName& TagName)
{
	TArray<UActorComponent*> ActorTriggerComponents = Actor->GetComponentsByTag(ULevelTriggerInterface::StaticClass(), TagName);

	for (UActorComponent* TriggerComponent : ActorTriggerComponents)
	{
		InputTriggerComponents.Add(TriggerComponent);
	}
}

USceneComponent* UTriggerComponent::FindTriggerComponentByName(USceneComponent* SceneComponent, const FName& Name)
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
		return FindTriggerComponentByName(ChildComponent, Name);
	}

	return nullptr;
}

void UTriggerComponent::__OnTriggerComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerComponents.Find(OverlappedComp) >= 0)
	{
		if (TriggerOnComponents.Find(OverlappedComp) < 0)
		{
			TriggerOnComponents.Add(OverlappedComp);
		}

		__ProcessTrigger(true);
	}
}

void UTriggerComponent::__OnTriggerComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TriggerOnComponents.Remove(OverlappedComp);

	__ProcessTrigger(false);
}

void UTriggerComponent::__GetTriggerComponents(TArray<TSoftObjectPtr<UActorComponent>>& InputTriggerComponents)
{
	InputTriggerComponents.Empty();

	if (ETriggerComponentFromType::ParentComponent == TriggerComponentFromType)
	{
		UPrimitiveComponent* AttachParentComponent = Cast<UPrimitiveComponent>(GetAttachParent());

		if (IsValid(AttachParentComponent))
		{
			InputTriggerComponents.Add(AttachParentComponent);
		}
	}
	else if (ETriggerComponentFromType::ComponentTagName == TriggerComponentFromType)
	{
		TArray<UActorComponent*> PrimitiveComponents = GetOwner()->GetComponentsByTag(UPrimitiveComponent::StaticClass(), ComponentTagName);

		for (UActorComponent* ActorComponent : PrimitiveComponents)
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);

			if (IsValid(PrimitiveComponent))
			{
				InputTriggerComponents.Add(PrimitiveComponent);
			}
		}
	}
	else if (ETriggerComponentFromType::ComponentName == TriggerComponentFromType)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(FindComponentByName(GetOwner()->GetRootComponent(), ComponentName));

		if (IsValid(PrimitiveComponent))
		{
			InputTriggerComponents.Add(PrimitiveComponent);
		}
	}
	else if (ETriggerComponentFromType::Actor == TriggerComponentFromType)
	{
		for (TSoftObjectPtr<AActor> TriggerActor : TriggerActors)
		{
			//UE_LOG(LogTemp, Display, TEXT("Koramga : <%s>(%s) : %s"), *GetOwner()->GetName(), *GetName(), *TriggerActor->GetName());

			FindTriggerComponent(InputTriggerComponents, TriggerActor->GetRootComponent());

			//UE_LOG(LogTemp, Display, TEXT("Koramga : <%s>(%s)"), *InputTriggerComponents[0]->GetOwner()->GetName(), *InputTriggerComponents[0]->GetName());
		}
	}
	else if (ETriggerComponentFromType::ActorComponentName == TriggerComponentFromType)
	{
		for (FTriggerActorWithName& TriggerActorWithName : TriggerActorWithNames)
		{
			if (TriggerActorWithName.Actor.IsValid())
			{
				for (FName& Name : TriggerActorWithName.Names)
				{
					InputTriggerComponents.Add(FindTriggerComponentByName(TriggerActorWithName.Actor->GetRootComponent(), Name));
				}
			}
		}
	}
	else if (ETriggerComponentFromType::ActorComponentTagName == TriggerComponentFromType)
	{
		for (FTriggerActorWithName& TriggerActorWithName : TriggerActorWithNames)
		{
			if (TriggerActorWithName.Actor.IsValid())
			{
				for (FName& Name : TriggerActorWithName.Names)
				{
					FindTriggerComponentByTagName(InputTriggerComponents, TriggerActorWithName.Actor.Get(), Name);
				}
			}
		}
	}
}

void UTriggerComponent::__ProcessTrigger(bool bInputIsOnTrigger)
{
	if (bInputIsOnTrigger)
	{
		if (false == bIsOnTrigger)
		{
			if (TriggerOnComponents.Num() == TriggerComponents.Num())
			{
				bIsOnTrigger = bInputIsOnTrigger;
				UpdateTrigger(bIsOnTrigger);
			}
		}
	}
	else
	{
		if (bIsOnTrigger)
		{
			if (TriggerOnComponents.Num() != TriggerComponents.Num())
			{
				bIsOnTrigger = bInputIsOnTrigger;
				UpdateTrigger(bIsOnTrigger);
			}
		}
	}
}

bool UTriggerComponent::IsOnTrigger() const
{
	return bIsOnTrigger;
}

void UTriggerComponent::GetTriggerLocation(TArray<FVector>& TriggerLocations)
{
	TArray<TSoftObjectPtr<UActorComponent>> InputTriggerComponents;

	__GetTriggerComponents(InputTriggerComponents);

	for (TSoftObjectPtr<UActorComponent> TriggerComponent : InputTriggerComponents)
	{
		if (TriggerComponent->IsA(USceneComponent::StaticClass()))
		{
			TriggerLocations.Add(Cast<USceneComponent>(TriggerComponent.Get())->GetComponentTransform().GetLocation());
		}
		else
		{
			TriggerLocations.Add(TriggerComponent->GetOwner()->GetActorLocation());
		}
	}
}

void UTriggerComponent::CallTriggerObservers(bool bIsInputOnTrigger)
{
	for (TSoftObjectPtr<ILevelTriggerInterface> ObserverLevelTriggerInterface : ObserverTriggerLevelInterfaces)
	{
		ObserverLevelTriggerInterface->CalledTriggerObservers(this, bIsInputOnTrigger);
	}
}

void UTriggerComponent::AddTriggerObserver(TSoftObjectPtr<ILevelTriggerInterface> LevelTriggerInterface)
{
	//UE_LOG(LogTemp, Display, TEXT("Koramga : (%s)<%s> Add Trigger Observer"), *GetOwner()->GetName(), *GetName());

	ObserverTriggerLevelInterfaces.Add(LevelTriggerInterface);
}

void UTriggerComponent::CalledTriggerObservers(TSoftObjectPtr<UActorComponent> CallerActorComponent, bool bIsInputOnTrigger)
{
	if (bIsInputOnTrigger)
	{
		if (TriggerComponents.Find(CallerActorComponent) >= 0)
		{
			TriggerOnComponents.Add(CallerActorComponent);
		}
	}
	else
	{
		TriggerOnComponents.Remove(CallerActorComponent);
	}

	__ProcessTrigger(bIsInputOnTrigger);
}

void UTriggerComponent::UpdateTrigger(bool bInputIsOnTrigger)
{
	CallTriggerObservers(bInputIsOnTrigger);
}
