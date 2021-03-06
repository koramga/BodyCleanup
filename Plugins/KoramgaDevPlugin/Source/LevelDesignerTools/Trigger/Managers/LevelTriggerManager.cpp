// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerManager.h"

#include "DrawDebugHelpers.h"
#include "../../Utility/LevelSupportFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void ULevelTriggerInterfaceSpace::SetupRelationship()
{
	ILevelTriggerInterface* CurrentLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());

	for (TSoftObjectPtr<UActorComponent>& TriggerComponent : TriggerComponents)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(TriggerComponent.Get());

		if (IsValid(PrimitiveComponent))
		{
			if (ETriggerPrimitiveComponentEventType::Overlap == CurrentLevelTriggerInterface->GetLevelTriggerSettings().TriggerPrimitiveComponentEventType)
			{
				PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapBegin);
				PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapEnd);

				const TArray<FOverlapInfo>& InputOverlapInfos = PrimitiveComponent->GetOverlapInfos();

				//We must be copy that. because of overlapinfo could be delete.
				TArray<FOverlapInfo> OverlapInfos;

				for (const FOverlapInfo& InputOverlapInfo : InputOverlapInfos)
				{
					OverlapInfos.Add(InputOverlapInfo);
				}

				for(const FOverlapInfo& OverlapInfo : OverlapInfos)
				{
					if (CurrentLevelTriggerInterface->IsApplyTriggerFromPrimitiveComopnent(OverlapInfo.OverlapInfo.GetComponent(), OverlapInfo.OverlapInfo.GetActor(), FHitResult()))
					{
						__AddTriggerComponentFromPrimitiveEvent(PrimitiveComponent, OverlapInfo.OverlapInfo.GetComponent());
					}
				}
			}
			else
			{
				//PrimitiveComponent->SetNotifyRigidBodyCollision(true);
				PrimitiveComponent->OnComponentHit.AddDynamic(this, &ULevelTriggerInterfaceSpace::__OnTriggerComponentHit);
			}
		}
		else
		{
			if (LevelTriggerManager.IsValid())
			{
				ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(Cast<ILevelTriggerInterface>(TriggerComponent.Get()));

				LevelTriggerInterfaceSpace->__AddTriggerObserver(this);
			}
		}
	}
}

void ULevelTriggerInterfaceSpace::SetLevelTriggerInterface(ILevelTriggerInterface* InputLevelTriggerInterface)
{
	LevelTriggerInterface = Cast<UObject>(InputLevelTriggerInterface);

	ULevelSupportFunctionLibrary::FindTriggerComponentFromLevelTriggerInput(TriggerComponents, InputLevelTriggerInterface);
}

void ULevelTriggerInterfaceSpace::SetLevelTriggerManager(const TSoftObjectPtr<ULevelTriggerManager>& InputLevelTriggerManager)
{
	LevelTriggerManager = InputLevelTriggerManager;
}

void ULevelTriggerInterfaceSpace::UpdateTrigger(bool bInputIsOnTrigger, bool bIsExternalCall)
{
	ILevelTriggerInterface* UpdateLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());

	const FLevelTriggerSettings& LevelTriggerSettings = UpdateLevelTriggerInterface->GetLevelTriggerSettings();

	if (ELevelTriggerWayType::OneWay == LevelTriggerSettings.LevelTriggerWayType)
	{
		if (bIsOnTrigger == bInputIsOnTrigger)
		{
			return;
		}

		bIsOnTrigger = bInputIsOnTrigger;

		__CallTriggerObservers(bIsOnTrigger);

		FLevelTriggerUpdateParam LevelTriggerUpdateParam;
		LevelTriggerUpdateParam.bIsOnTrigger = bIsOnTrigger;
		UpdateLevelTriggerInterface->UpdateTrigger(LevelTriggerUpdateParam);
	}
	else if (ELevelTriggerWayType::TwoWay == LevelTriggerSettings.LevelTriggerWayType)
	{
		if (bIsExternalCall)
		{
			if (bIsOnTwoWayTrigger == bInputIsOnTrigger)
			{
				return;
			}

			bIsOnTwoWayTrigger = bInputIsOnTrigger;

			__CallTriggerObservers(bIsOnTwoWayTrigger);
		}
		else
		{
			if (bIsOnTrigger == bInputIsOnTrigger)
			{
				return;
			}

			bIsOnTrigger = bInputIsOnTrigger;

			FLevelTriggerUpdateParam LevelTriggerUpdateParam;
			LevelTriggerUpdateParam.bIsOnTrigger = bIsOnTrigger;
			UpdateLevelTriggerInterface->UpdateTrigger(LevelTriggerUpdateParam);
		}
	}
}

bool ULevelTriggerInterfaceSpace::HasTriggerComponents() const
{
	return 0 < TriggerComponents.Num();
}

void ULevelTriggerInterfaceSpace::__AddTriggerComponentFromPrimitiveEvent(UPrimitiveComponent* TriggerComponent, UPrimitiveComponent* OtherComp)
{
	if (TriggerComponents.Find(TriggerComponent) >= 0)
	{
		FLevelTriggerCertificate* LevelTriggerCertificate = TriggerCertificateComponents.Find(TriggerComponent);

		if (LevelTriggerCertificate == nullptr)
		{
			//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger On Create : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

			FLevelTriggerCertificate& Data = TriggerCertificateComponents.Add(TriggerComponent, FLevelTriggerCertificate(TriggerComponent));
			Data.OtherComps.Add(OtherComp);
			ProcessTrigger(true);
		}
		else
		{
			if (LevelTriggerCertificate->OtherComps.Find(OtherComp) < 0)
			{
				//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger On Add : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

				LevelTriggerCertificate->OtherComps.Add(OtherComp);
			}
		}
	}
}

void ULevelTriggerInterfaceSpace::__RemoveTriggerComponentFromPrimitiveEvent(UPrimitiveComponent* TriggerComponent, UPrimitiveComponent* OtherComp)
{
	FLevelTriggerCertificate* TriggerCertificate = TriggerCertificateComponents.Find(TriggerComponent);

	if (nullptr != TriggerCertificate)
	{
		//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger Off Remove : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

		TriggerCertificate->OtherComps.Remove(OtherComp);

		if (TriggerCertificate->OtherComps.Num() <= 0)
		{
			//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger Off Delete : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());
			TriggerCertificateComponents.Remove(TriggerComponent);
			ProcessTrigger(false);
		}
	}
}

void ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ILevelTriggerInterface* CurrentLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());

	if (CurrentLevelTriggerInterface->IsApplyTriggerFromPrimitiveComopnent(OtherComp, OtherActor, SweepResult))
	{
		__AddTriggerComponentFromPrimitiveEvent(OverlappedComp, OtherComp);
	}
}

void ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	__RemoveTriggerComponentFromPrimitiveEvent(OverlappedComp, OtherComp);
}

void ULevelTriggerInterfaceSpace::__OnTriggerComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ILevelTriggerInterface* CurrentLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());

	if (CurrentLevelTriggerInterface->IsApplyTriggerFromPrimitiveComopnent(OtherComp, OtherActor, Hit))
	{
		__AddTriggerComponentFromPrimitiveEvent(HitComponent, OtherComp);

		ProcessTrigger(true);

		__RemoveTriggerComponentFromPrimitiveEvent(HitComponent, OtherComp);
	}
}

void ULevelTriggerInterfaceSpace::ProcessTrigger(bool bInputIsOnTrigger)
{
	if (bIsOnTrigger != bInputIsOnTrigger)
	{
		if (LevelTriggerInterface.IsValid())
		{
			ILevelTriggerInterface* UpdateLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());
			const FLevelTriggerInputFrom* LevelTriggerInputFrom = UpdateLevelTriggerInterface->GetLevelTriggerInputFrom();

			if (ELevelTriggerReactType::Once == LevelTriggerInputFrom->LevelTriggerReactType)
			{
				//????????? ??? ??? ?????????????????? ????????? ??????.
				if (bIsOnTrigger)
				{
					return;
				}
			}

			if (bInputIsOnTrigger)
			{
				if (TriggerCertificateComponents.Num() == TriggerComponents.Num())
				{
					UpdateTrigger(true);
				}
			}
			else
			{
				if (TriggerCertificateComponents.Num() != TriggerComponents.Num())
				{
					UpdateTrigger(false);
				}
			}
		}
	}
}

void ULevelTriggerInterfaceSpace::Release()
{
	//????????? ??????
	for (TSoftObjectPtr<UActorComponent>& TriggerComponent : TriggerComponents)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(TriggerComponent.Get());
	
		if (IsValid(PrimitiveComponent))
		{
			PrimitiveComponent->OnComponentBeginOverlap.Remove(this, TEXT("__OnTriggerComponentOverlapBegin"));
			PrimitiveComponent->OnComponentEndOverlap.Remove(this, TEXT("__OnTriggerComponentOverlapEnd"));
		}
		else
		{
			if (LevelTriggerManager.IsValid())
			{
				ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(Cast<ILevelTriggerInterface>(TriggerComponent.Get()));

				if(nullptr != LevelTriggerInterfaceSpace)
				{
					LevelTriggerInterfaceSpace->__RemoveTriggerObserver(this);
				}				
			}
		}
	}
	
	for (TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace : ObserverTriggerLevelInterfaceSpaces)
	{
		LevelTriggerInterfaceSpace->__RemoveTriggerComponent(Cast<UActorComponent>(LevelTriggerInterface.Get()));
	}
}

void ULevelTriggerInterfaceSpace::__CalledTriggerObservers(const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& CallerLevelTriggerInterfaceSpace, bool bIsInputOnTrigger)
{
	if (CallerLevelTriggerInterfaceSpace.IsValid())
	{
		UActorComponent* ActorComponent = Cast<UActorComponent>(CallerLevelTriggerInterfaceSpace->LevelTriggerInterface.Get());

		if (bIsInputOnTrigger)
		{
			if (TriggerComponents.Contains(ActorComponent))
			{
				TriggerCertificateComponents.Add(ActorComponent, FLevelTriggerCertificate(ActorComponent));
			}
		}
		else
		{
			TriggerCertificateComponents.Remove(ActorComponent);
		}

		ProcessTrigger(bIsInputOnTrigger);
	}
}

void ULevelTriggerInterfaceSpace::__CallTriggerObservers(bool bIsInputOnTrigger)
{
	TArray<TSoftObjectPtr<ULevelTriggerInterfaceSpace>> KillSafeArray;

	for (TSoftObjectPtr<ULevelTriggerInterfaceSpace> ObserverLevelTriggerInterfaceSpace : ObserverTriggerLevelInterfaceSpaces)
	{
		KillSafeArray.Add(ObserverLevelTriggerInterfaceSpace);
	}

	for (TSoftObjectPtr<ULevelTriggerInterfaceSpace> ObserverLevelTriggerInterfaceSpace : KillSafeArray)
	{
		if (ObserverLevelTriggerInterfaceSpace.IsValid())
		{
			ObserverLevelTriggerInterfaceSpace->__CalledTriggerObservers(this, bIsInputOnTrigger);
		}
	}
}

void ULevelTriggerInterfaceSpace::__AddTriggerObserver(const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace)
{
	ObserverTriggerLevelInterfaceSpaces.Add(LevelTriggerInterfaceSpace);
}

void ULevelTriggerInterfaceSpace::__RemoveTriggerObserver(const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace)
{
	ObserverTriggerLevelInterfaceSpaces.Remove(LevelTriggerInterfaceSpace);
}

void ULevelTriggerInterfaceSpace::__RemoveTriggerComponent(UActorComponent* RemoveActorComponent)
{
	if (IsValid(RemoveActorComponent))
	{
		bool bContainedTriggerComponents = false;
		bool bContainedCertificateComponents = false;


		if (TriggerComponents.Contains(RemoveActorComponent))
		{
			TriggerComponents.Remove(RemoveActorComponent);
			bContainedTriggerComponents = true;
		}

		if (TriggerCertificateComponents.Contains(RemoveActorComponent))
		{
			TriggerCertificateComponents.Remove(RemoveActorComponent);
			bContainedCertificateComponents = true;
		}

		if (bContainedTriggerComponents != bContainedCertificateComponents)
		{
			ProcessTrigger(false);
		}		
	}
}

void ULevelTriggerInterfaceSpace::FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace) const
{
	const FLevelTriggerInputFrom* ParamLevelTriggerInputFrom = Cast<ILevelTriggerInterface>(LevelTriggerInterfaceSpace->LevelTriggerInterface.Get())->GetLevelTriggerInputFrom();
	
	if (ELevelTriggerInputNodeFromType::Parent == ParamLevelTriggerInputFrom->LevelTriggerInputNodeFromType)
	{
		for (const auto& TriggerCertificateComponent : LevelTriggerInterfaceSpace->TriggerCertificateComponents)
		{
			for (const TSoftObjectPtr<UPrimitiveComponent>& PrimitiveComponent : TriggerCertificateComponent.Value.OtherComps)
			{
				if (Actors.Find(PrimitiveComponent->GetOwner()) < 0)
				{
					Actors.Add(PrimitiveComponent->GetOwner());
				}
			}
		}
	}
	else if (ELevelTriggerInputNodeFromType::Setup == ParamLevelTriggerInputFrom->LevelTriggerInputNodeFromType)
	{
		for (const auto& TriggerCertificateComponent : LevelTriggerInterfaceSpace->TriggerCertificateComponents)
		{
			if (TriggerCertificateComponent.Key->IsA(UPrimitiveComponent::StaticClass()))
			{
				for (const TSoftObjectPtr<UPrimitiveComponent>& PrimitiveComponent : TriggerCertificateComponent.Value.OtherComps)
				{
					if (Actors.Find(PrimitiveComponent->GetOwner()) < 0)
					{
						Actors.Add(PrimitiveComponent->GetOwner());
					}
				}
			}			
		}
	
		for (TSoftObjectPtr<UActorComponent> TriggerComponentParam : LevelTriggerInterfaceSpace->TriggerComponents)
		{
			ILevelTriggerInterface* ParamLevelTriggerInterface = Cast<ILevelTriggerInterface>(TriggerComponentParam.Get());
	
			ULevelTriggerInterfaceSpace* ParamLevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(ParamLevelTriggerInterface);
			
			if (nullptr != ParamLevelTriggerInterfaceSpace)
			{
				FindOverlapActors(Actors, ParamLevelTriggerInterfaceSpace);
			}
		}
	}
}

const ILevelTriggerInterface* ULevelTriggerInterfaceSpace::GetLevelTriggerInterface() const
{
	return Cast< const ILevelTriggerInterface>(LevelTriggerInterface.Get());
}

const TArray<TSoftObjectPtr<UActorComponent>>& ULevelTriggerInterfaceSpace::GetTriggerComponents() const
{
	return TriggerComponents;
}

void ULevelTriggerInterfaceSpace::GetTriggerPrimitiveComponents(
	TArray<TSoftObjectPtr<UPrimitiveComponent>>& TriggerPrimitiveComponents) const
{
	for (const TSoftObjectPtr<UActorComponent>& TriggerComponent : TriggerComponents)
	{
		if(TriggerComponent.IsValid())
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(TriggerComponent.Get());

			if (IsValid(PrimitiveComponent))
			{
				TriggerPrimitiveComponents.Add(PrimitiveComponent);
			}			
		}
	}
}

const FLevelTriggerCertificate* ULevelTriggerInterfaceSpace::GetLevelTriggerCertificate(UObject* Key) const
{
	return TriggerCertificateComponents.Find(Key);
}

ULevelTriggerInterfaceSpace* ULevelTriggerManager::GetLevelTriggerInterfaceSpace(const ILevelTriggerInterface* TriggerInterface) const
{
	if (nullptr == TriggerInterface)
	{
		return nullptr;
	}

	ULevelTriggerInterfaceSpace* LevelTriggerInterface = LevelTriggerInterfaceSpaces.FindRef(Cast<UObject>(TriggerInterface));

	return LevelTriggerInterface;
}

void ULevelTriggerManager::RegisterTrigger(ILevelTriggerInterface* TriggerInterface)
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterface = LevelTriggerInterfaceSpaces.FindRef(Cast<UObject>(TriggerInterface));

	if (nullptr == LevelTriggerInterface)
	{
		LevelTriggerInterface = Cast<ULevelTriggerInterfaceSpace>(NewObject<ULevelTriggerInterfaceSpace>(this));

		LevelTriggerInterface->SetLevelTriggerManager(this);
		LevelTriggerInterface->SetLevelTriggerInterface(TriggerInterface);

		LevelTriggerInterfaceSpaces.Add(Cast<UObject>(TriggerInterface), LevelTriggerInterface);
		RegisterTriggerInterfaceSpaces.Add(LevelTriggerInterface);
	}

}

void ULevelTriggerManager::UnRegisterTrigger(ILevelTriggerInterface* TriggerInterface)
{
	UObject* UnRegisterTrigger = Cast<UObject>(TriggerInterface);

	ULevelTriggerInterfaceSpace* LevelTriggerInterface = LevelTriggerInterfaceSpaces.FindRef(UnRegisterTrigger);

	if (nullptr != LevelTriggerInterface)
	{
		LevelTriggerInterface->Release();
		LevelTriggerInterfaceSpaces.Remove(UnRegisterTrigger);
	}
}

void ULevelTriggerManager::FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, const ILevelTriggerInterface* TriggerInterface) const
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(TriggerInterface);
	
	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->FindOverlapActors(Actors, LevelTriggerInterfaceSpace);
	}
}

void ULevelTriggerManager::UpdateTrigger(ILevelTriggerInterface* LevelTriggerInterface, bool bInputIsOnTrigger)
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(LevelTriggerInterface);

	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->UpdateTrigger(bInputIsOnTrigger, true);
	}
}

void ULevelTriggerManager::UpdateTriggerOnce(ILevelTriggerInterface* LevelTriggerInterface)
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(LevelTriggerInterface);

	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->UpdateTrigger(true, true);
		LevelTriggerInterfaceSpace->UpdateTrigger(false, true);
	}
}

void ULevelTriggerManager::Tick(float DeltaSeconds)
{
	if(RegisterTriggerInterfaceSpaces.Num() > 0)
	{
		for (auto& LevelTriggerInterfaceSpace : RegisterTriggerInterfaceSpaces)
		{
			if(LevelTriggerInterfaceSpace.IsValid())
			{
				if (LevelTriggerInterfaceSpace->HasTriggerComponents())
				{
					LevelTriggerInterfaceSpace->SetupRelationship();
				}				
			}
		}

		for (const auto& LevelTriggerInterfaceSpace : RegisterTriggerInterfaceSpaces)
		{
			if(LevelTriggerInterfaceSpace.IsValid())
			{
				const ILevelTriggerInterface* LevelTriggerInterface = LevelTriggerInterfaceSpace->GetLevelTriggerInterface();

				if (nullptr != LevelTriggerInterface)
				{
					const FLevelTriggerInputFrom* LevelTriggerInputFrom = LevelTriggerInterface->GetLevelTriggerInputFrom();

					if (nullptr != LevelTriggerInputFrom)
					{
						if (ELevelTriggerInputNodeFromType::Action != LevelTriggerInputFrom->LevelTriggerInputNodeFromType)
						{
							LevelTriggerInterfaceSpace->ProcessTrigger(true);
						}
					}
				}				
			}
		}

		RegisterTriggerInterfaceSpaces.Empty();		
	}	
}

void ULevelTriggerManager::SetupTriggerAfterSpawn(AActor* Actor)
{
	const TSet<UActorComponent*>& Components = Actor->GetComponents();

	for (UActorComponent* ActorComponent : Components)
	{
		if (ActorComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
		{
			ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(Cast<ILevelTriggerInterface>(ActorComponent));

			if (IsValid(LevelTriggerInterfaceSpace))
			{
				LevelTriggerInterfaceSpace->SetupRelationship();
			}
		}
	}
}
