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
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//if (ETriggerComponentTickType::Tick == TriggerComponentTickType)
	//{
	//	if (false == bIsTick)
	//	{
	//		if (TriggerComponents.Num() == TriggerTickComponents.Num())
	//		{
	//
	//		}
	//
	//		bIsTick = __ProcessIsTick();
	//	}
	//}
	//else
	//{
	//	bIsTick = __ProcessIsTick();
	//}
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
		return FindComponentByName(SceneComponent, Name);
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
		FindTriggerComponent(InputTriggerComponents, SceneComponent);
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
		return FindTriggerComponentByName(SceneComponent, Name);
	}

	return nullptr;
}

void UTriggerComponent::__OnTriggerComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerComponents.Find(OtherComp) >= 0)
	{
		if (false == TriggerTickComponents.Find(OtherComp))
		{
			TriggerTickComponents.Add(OtherComp);
		}

		__ProcessTick(bIsTick);
	}
}

void UTriggerComponent::__OnTriggerComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TriggerTickComponents.Remove(OtherComp);

	__ProcessTick(bIsTick);
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
			//AttachParentComponent->OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapBegin);
			//AttachParentComponent->OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapEnd);
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
				//PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapBegin);
				//PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapEnd);
			}
		}
	}
	else if (ETriggerComponentFromType::ComponentName == TriggerComponentFromType)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(FindComponentByName(GetOwner()->GetRootComponent(), ComponentName));

		if (IsValid(PrimitiveComponent))
		{
			InputTriggerComponents.Add(PrimitiveComponent);
			//PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapBegin);
			//PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapEnd);
		}
	}
	else if (ETriggerComponentFromType::Actor == TriggerComponentFromType)
	{
		for (TSoftObjectPtr<AActor> TriggerActor : TriggerActors)
		{
			FindTriggerComponent(InputTriggerComponents, TriggerActor->GetRootComponent());
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

bool UTriggerComponent::__ProcessIsTick()
{
	if (ETriggerComponentFromType::Actor == TriggerComponentFromType
		|| ETriggerComponentFromType::ActorComponentName == TriggerComponentFromType
		|| ETriggerComponentFromType::ActorComponentTagName == TriggerComponentFromType)
	{
		TriggerTickComponents.Empty();

		for (TSoftObjectPtr<UActorComponent> TriggerComponent : TriggerComponents)
		{
			if (TriggerComponent.IsValid())
			{
				ILevelTriggerInterface* LevelTriggerInterface = Cast<ILevelTriggerInterface>(TriggerComponent.Get());

				if (nullptr != LevelTriggerInterface)
				{
					if (LevelTriggerInterface->IsOnTrigger())
					{
						TriggerTickComponents.Add(TriggerComponent);
					}
				}
			}
		}
	}

	if (TriggerComponents.Num() == TriggerTickComponents.Num())
	{
		return true;
	}

	return false;
}

void UTriggerComponent::__ProcessTick(bool bInputIsTick)
{
	if (bInputIsTick)
	{
		if (false == bIsTick)
		{
			if (TriggerTickComponents.Num() == TriggerComponents.Num())
			{
				bIsTick = !bInputIsTick;
				CallTriggerObservers(bIsTick);
			}
		}
	}
	else
	{
		if (bIsTick)
		{
			if (TriggerTickComponents.Num() != TriggerComponents.Num())
			{
				bIsTick = !bInputIsTick;
				CallTriggerObservers(bIsTick);
			}
		}
	}
}

bool UTriggerComponent::IsOnTrigger() const
{
	return bIsTick;
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

void UTriggerComponent::CallTriggerObservers(bool bInputIsTick)
{
	for (TSoftObjectPtr<ILevelTriggerInterface> ObserverLevelTriggerInterface : ObserverTriggerLevelInterfaces)
	{
		ObserverLevelTriggerInterface->CalledTriggerObservers(this, bInputIsTick);
	}
}

void UTriggerComponent::AddTriggerObserver(TSoftObjectPtr<ILevelTriggerInterface> LevelTriggerInterface)
{
	ObserverTriggerLevelInterfaces.Add(LevelTriggerInterface);
}

void UTriggerComponent::CalledTriggerObservers(TSoftObjectPtr<UActorComponent> CallerActorComponent, bool bInputIsTick)
{
	if (bInputIsTick)
	{
		if (TriggerComponents.Find(CallerActorComponent) >= 0)
		{
			TriggerTickComponents.Add(CallerActorComponent);
		}
	}
	else
	{
		TriggerTickComponents.Remove(CallerActorComponent);
	}

	__ProcessTick(bInputIsTick);
}