// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerManager.h"
#include "../../Utility/LevelSupportFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void ULevelTriggerInterfaceSpace::SetupRelationship()
{
	for (TSoftObjectPtr<UActorComponent>& TriggerComponent : TriggerComponents)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(TriggerComponent.Get());

		if (IsValid(PrimitiveComponent))
		{
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapBegin);
			PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapEnd);
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
	if (bIsExternalCall)
	{
		if (bIsOnExternalTrigger == bInputIsOnTrigger)
		{
			return;
		}

		bIsOnExternalTrigger = bInputIsOnTrigger;
	}
	else
	{
		if (bIsOnInternalTrigger == bInputIsOnTrigger)
		{
			return;
		}

		bIsOnInternalTrigger = bInputIsOnTrigger;
	}

	ILevelTriggerInterface* UpdateLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());

	bool bIsCallObserver = false;

	if (ELevelTriggerObserverCallType::External == LevelTriggerObserverCallType
		&& bIsExternalCall)
	{
		bIsCallObserver = true;
	}
	else if (ELevelTriggerObserverCallType::Internal == LevelTriggerObserverCallType
		&& false == bIsExternalCall)
	{
		bIsCallObserver = true;
	}

	if (true == bIsCallObserver)
	{
		__CallTriggerObservers(bInputIsOnTrigger);
	}

	if (false == bIsExternalCall)
	{
		UpdateLevelTriggerInterface->UpdateTrigger(bIsExternalCall, bIsOnTrigger);

		if (ELevelTriggerObserverCallType::External == LevelTriggerObserverCallType)
		{
			bIsOnTrigger = false;
		}
	}
}

bool ULevelTriggerInterfaceSpace::HasTriggerComponents() const
{
	return 0 < TriggerComponents.Num();
}

void ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerComponents.Find(OverlappedComp) >= 0)
	{
		FLevelTriggerCertificate* LevelTriggerCertificate = TriggerCertificateComponents.Find(OverlappedComp);

		if (LevelTriggerCertificate == nullptr)
		{
			//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger On Create : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

			FLevelTriggerCertificate& Data = TriggerCertificateComponents.Add(OverlappedComp, FLevelTriggerCertificate(OverlappedComp));
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

void ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FLevelTriggerCertificate* TriggerCertificate = TriggerCertificateComponents.Find(OverlappedComp);

	if (nullptr != TriggerCertificate)
	{
		//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger Off Remove : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());

		TriggerCertificate->OtherComps.Remove(OtherComp);

		if (TriggerCertificate->OtherComps.Num() <= 0)
		{
			//UE_LOG(LogTemp, Display, TEXT("Koramga Trigger Off Delete : <%s>(%s) : %s"), *OtherActor->GetName(), *OtherComp->GetName(), *OverlappedComp->GetName());
			TriggerCertificateComponents.Remove(OverlappedComp);
			ProcessTrigger(false);
		}
	}
}

void ULevelTriggerInterfaceSpace::ProcessTrigger(bool bInputIsOnTrigger)
{
	if (bIsOnTrigger != bInputIsOnTrigger)
	{
		ILevelTriggerInterface* UpdateLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());
		const FLevelTriggerInputFrom* LevelTriggerInputFrom = UpdateLevelTriggerInterface->GetLevelTriggerInputFrom();

		if (ELevelTriggerReactType::Once == LevelTriggerInputFrom->LevelTriggerReactType)
		{
			//일전에 한 번 호출되었다는 의미가 된다.
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
	for (TSoftObjectPtr<ULevelTriggerInterfaceSpace> ObserverLevelTriggerInterfaceSpace : ObserverTriggerLevelInterfaceSpaces)
	{
		ObserverLevelTriggerInterfaceSpace->__CalledTriggerObservers(this, bIsInputOnTrigger);
	}
}

void ULevelTriggerInterfaceSpace::__AddTriggerObserver(const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace)
{
	ObserverTriggerLevelInterfaceSpaces.Add(LevelTriggerInterfaceSpace);
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

ULevelTriggerInterfaceSpace* ULevelTriggerManager::GetLevelTriggerInterfaceSpace(ILevelTriggerInterface* TriggerInterface) const
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
	}

}

void ULevelTriggerManager::FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, ILevelTriggerInterface* TriggerInterface) const
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(TriggerInterface);
	
	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->FindOverlapActors(Actors, LevelTriggerInterfaceSpace);
	}
}

void ULevelTriggerManager::BeginPlay()
{
	for (auto& LevelTriggerInterfaceSpace : LevelTriggerInterfaceSpaces)
	{
		if (LevelTriggerInterfaceSpace.Value->HasTriggerComponents())
		{
			LevelTriggerInterfaceSpace.Value->SetupRelationship();
		}
	}

	for (const auto& LevelTriggerInterfaceSpace : LevelTriggerInterfaceSpaces)
	{
		const ILevelTriggerInterface* LevelTriggerInterface = LevelTriggerInterfaceSpace.Value->GetLevelTriggerInterface();

		if (nullptr != LevelTriggerInterface)
		{
			const FLevelTriggerInputFrom* LevelTriggerInputFrom = LevelTriggerInterface->GetLevelTriggerInputFrom();

			if (nullptr != LevelTriggerInputFrom)
			{
				if (ELevelTriggerInputNodeFromType::Action != LevelTriggerInputFrom->LevelTriggerInputNodeFromType)
				{
					LevelTriggerInterfaceSpace.Value->ProcessTrigger(true);
				}
			}
		}
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