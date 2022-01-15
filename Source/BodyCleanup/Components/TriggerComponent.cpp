// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "../Utilities/FunctionLibraries/FindFunctionLibrary.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bIsCanControlTriggerComponentFromType = true;
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	__GetTriggerComponents(TriggerComponents);

	for (TSoftObjectPtr<USceneComponent> TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
		{
			Cast<ILevelTriggerInterface>(TriggerComponent.Get())->AddTriggerObserver(this);
		}
		else if (TriggerComponent->IsA(UPrimitiveComponent::StaticClass()))
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(TriggerComponent.Get());

			PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapEnd);
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapBegin);
		}
	}
}

void UTriggerComponent::__OnTriggerComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerComponents.Find(OverlappedComp) >= 0)
	{
		FTriggerOnData* TriggerOnData = TriggerOnComponents.Find(OverlappedComp);

		if (TriggerOnData == nullptr)
		{
			//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger On Create : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

			FTriggerOnData& Data = TriggerOnComponents.Add(OverlappedComp, FTriggerOnData(OverlappedComp));
			Data.OtherComps.Add(OtherComp);
			__ProcessTrigger(true);
		}
		else
		{
			if (TriggerOnData->OtherComps.Find(OtherComp) < 0)
			{
				//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger On Add : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

				TriggerOnData->OtherComps.Add(OtherComp);
			}
		}
	}
}

void UTriggerComponent::__OnTriggerComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FTriggerOnData* TriggerOnData = TriggerOnComponents.Find(OverlappedComp);

	if (nullptr != TriggerOnData)
	{
		//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger Off Remove : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

		TriggerOnData->OtherComps.Remove(OtherComp);

		if (TriggerOnData->OtherComps.Num() <= 0)
		{
			//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger Off Delete : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());
			TriggerOnComponents.Remove(OverlappedComp);
			__ProcessTrigger(false);
		}
	}
}

void UTriggerComponent::__GetTriggerComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents)
{
	InputTriggerComponents.Empty();

	TArray<TSoftObjectPtr<USceneComponent>> FindComponents;

	if (ETriggerComponentFromType::Parent == TriggerComponentFromType)
	{
		FindComponents.Add(GetAttachParent());
	}
	else if (ETriggerComponentFromType::Setup == TriggerComponentFromType)
	{
		for (const FTriggerActorWithName& TriggerActorWithName : TriggerActorWithNames)
		{
			TSoftObjectPtr<AActor> TriggerActor = GetOwner();

			if (TriggerActorWithName.Actor.IsValid())
			{
				TriggerActor = TriggerActorWithName.Actor;
			}

			if (TriggerActor.IsValid())
			{
				if (TriggerActorWithName.Names.Num() > 0)
				{
					if (ENameType::Name == TriggerActorWithName.NameType)
					{
						UFindFunctionLibrary::FindComponentsByNames(FindComponents, TriggerActor->GetRootComponent(), TriggerActorWithName.Names);
					}
					else
					{
						for (const FName& Name : TriggerActorWithName.Names)
						{
							TArray<UActorComponent*> ActorComponents = TriggerActor->GetComponentsByTag(USceneComponent::StaticClass(), Name);

							for (UActorComponent* ActorComponent : ActorComponents)
							{
								USceneComponent* SceneComponent = Cast<USceneComponent>(ActorComponent);

								if (IsValid(SceneComponent))
								{
									FindComponents.Add(SceneComponent);
								}
							}
						}
					}
				}
				else
				{
					UFindFunctionLibrary::FindTriggerComponents(FindComponents, TriggerActor->GetRootComponent());
				}
			}
		}
	}

	__AddTriggerComponents(InputTriggerComponents, FindComponents);
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

void UTriggerComponent::__FindTriggerOnActors(TArray<TSoftObjectPtr<AActor>>& Actors, const TSoftObjectPtr<UTriggerComponent> TriggerComponent)
{
	if (ETriggerComponentFromType::Parent == TriggerComponent->TriggerComponentFromType)
	{
		for (const auto& TriggerOnComponent : TriggerComponent->TriggerOnComponents)
		{
			for (const TSoftObjectPtr<UPrimitiveComponent>& PrimitiveComponent : TriggerOnComponent.Value.OtherComps)
			{
				if (Actors.Find(PrimitiveComponent->GetOwner()) < 0)
				{
					Actors.Add(PrimitiveComponent->GetOwner());
				}
			}
		}
	}
	else if (ETriggerComponentFromType::Setup == TriggerComponent->TriggerComponentFromType)
	{
		for (auto& TriggerOnComponent : TriggerComponent->TriggerOnComponents)
		{
			if (TriggerOnComponent.Key->IsA(UPrimitiveComponent::StaticClass()))
			{
				for (const TSoftObjectPtr<UPrimitiveComponent>& PrimitiveComponent : TriggerOnComponent.Value.OtherComps)
				{
					if (Actors.Find(PrimitiveComponent->GetOwner()) < 0)
					{
						Actors.Add(PrimitiveComponent->GetOwner());
					}
				}
			}			
		}

		for (TSoftObjectPtr<UActorComponent> TriggerComponentParam : TriggerComponent->TriggerComponents)
		{
			TSoftObjectPtr<UTriggerComponent> SetTriggerComponent = Cast<UTriggerComponent>(TriggerComponentParam.Get());

			if (SetTriggerComponent.IsValid())
			{
				__FindTriggerOnActors(Actors, SetTriggerComponent);
			}
		}
	}
}

void UTriggerComponent::__AddTriggerComponents(TArray<TSoftObjectPtr<USceneComponent>>& DestTriggerComponents, const TArray<TSoftObjectPtr<USceneComponent>>& PushComponents)
{
	for (TSoftObjectPtr<USceneComponent> SceneComponent : PushComponents)
	{
		if (SceneComponent.IsValid()
			&& this != SceneComponent)
		{
			if (SceneComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
			{
				DestTriggerComponents.Push(SceneComponent);
			}
			else if(SceneComponent->IsA(UPrimitiveComponent::StaticClass()))
			{
				DestTriggerComponents.Push(SceneComponent);
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
	TArray<TSoftObjectPtr<USceneComponent>> InputTriggerComponents;

	__GetTriggerComponents(InputTriggerComponents);

	for (TSoftObjectPtr<USceneComponent> TriggerComponent : InputTriggerComponents)
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

void UTriggerComponent::CalledTriggerObservers(TSoftObjectPtr<USceneComponent> CallerActorComponent, bool bIsInputOnTrigger)
{
	if (bIsInputOnTrigger)
	{
		if (TriggerComponents.Find(CallerActorComponent) >= 0)
		{
			TriggerOnComponents.Add(CallerActorComponent, FTriggerOnData(CallerActorComponent));
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

void UTriggerComponent::FindTriggerOnActors(TArray<TSoftObjectPtr<AActor>>& Actors)
{
	__FindTriggerOnActors(Actors, this);
}