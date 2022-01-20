// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerManager.h"
#include "../../Utility/LevelSupportFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void ULevelTriggerInterfaceSpace::Initialize()
{
	ULevelSupportFunctionLibrary::FindTriggerComponentFromLevelTriggerInput(TriggerComponents, LevelTriggerInterface.Get());
	
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
				ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(LevelTriggerInterface.Get());
	
				LevelTriggerInterfaceSpace->__AddTriggerObserver(this);
			}
		}
	}
}

void ULevelTriggerInterfaceSpace::SetLevelTriggerInterface(const TSoftObjectPtr<ILevelTriggerInterface>& InputLevelTriggerInterface)
{
	LevelTriggerInterface = InputLevelTriggerInterface;
}

void ULevelTriggerInterfaceSpace::SetLevelTriggerManager(const TSoftObjectPtr<ULevelTriggerManager>& InputLevelTriggerManager)
{
	LevelTriggerManager = InputLevelTriggerManager;
}

void ULevelTriggerInterfaceSpace::UpdateTrigger(bool bInputIsOnTrigger)
{
	LevelTriggerInterface->UpdateTrigger(bInputIsOnTrigger);
}

void ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			__ProcessTrigger(false);
		}
	}
}

void ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ULevelTriggerInterfaceSpace::__ProcessTrigger(bool bInputIsOnTrigger)
{
	if (bInputIsOnTrigger)
	{
		if (false == bIsOnTrigger)
		{
			if (TriggerCertificateComponents.Num() == TriggerComponents.Num())
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
			if (TriggerCertificateComponents.Num() != TriggerComponents.Num())
			{
				bIsOnTrigger = bInputIsOnTrigger;
				UpdateTrigger(bIsOnTrigger);
			}
		}
	}
}

void ULevelTriggerInterfaceSpace::__CalledTriggerObservers(TSoftObjectPtr<USceneComponent> CallerActorComponent, bool bIsInputOnTrigger)
{
	if (bIsInputOnTrigger)
	{
		if (TriggerComponents.Find(CallerActorComponent) >= 0)
		{
			TriggerCertificateComponents.Add(CallerActorComponent, FLevelTriggerCertificate(CallerActorComponent));
		}
	}
	else
	{
		TriggerCertificateComponents.Remove(CallerActorComponent);
	}

	__ProcessTrigger(bIsInputOnTrigger);
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


void ULevelTriggerInterfaceSpace::FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, const TSoftObjectPtr<ULevelTriggerInterfaceSpace>& LevelTriggerInterfaceSpace)
{
	const FLevelTriggerInput* ParamLevelTriggerInput = LevelTriggerInterfaceSpace->LevelTriggerInterface->GetLevelTriggerInput();
	
	if (ELevelTriggerInputNodeType::Parent == ParamLevelTriggerInput->LevelTriggerInputNodeType)
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
	else if (ELevelTriggerInputNodeType::Setup == ParamLevelTriggerInput->LevelTriggerInputNodeType)
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
			//TSoftObjectPtr<ILevelTriggerInterface> LevelTriggerInterfaceSoftObjectPtr = TSoftObjectPtr<ILevelTriggerInterface>(ParamLevelTriggerInterface);
	
			ULevelTriggerInterfaceSpace* ParamLevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(ParamLevelTriggerInterface);
			
			if (nullptr != LevelTriggerInterfaceSpace)
			{
				FindOverlapActors(Actors, LevelTriggerInterfaceSpace);
			}
		}
	}
}

ULevelTriggerInterfaceSpace* ULevelTriggerManager::GetLevelTriggerInterfaceSpace(TSoftObjectPtr<ILevelTriggerInterface> TriggerInterface)
{
	if (nullptr == TriggerInterface)
	{
		return nullptr;
	}

	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = LevelTriggerInterfaces.FindRef(TriggerInterface);

	if (nullptr == LevelTriggerInterfaceSpace)
	{
		ULevelTriggerInterfaceSpace* NewLevelTriggerInterfaceSpace = Cast<ULevelTriggerInterfaceSpace>(NewObject<ULevelTriggerInterfaceSpace>(this));
	
		NewLevelTriggerInterfaceSpace->SetLevelTriggerManager(this);
		NewLevelTriggerInterfaceSpace->SetLevelTriggerInterface(TriggerInterface);
	
		LevelTriggerInterfaceSpace = LevelTriggerInterfaces.Add(TriggerInterface, NewLevelTriggerInterfaceSpace);
	}

	return LevelTriggerInterfaceSpace;
}

void ULevelTriggerManager::InitializeTriggerInterfaceSpace(const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface)
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(TriggerInterface);
	
	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->Initialize();
	}
}

void ULevelTriggerManager::FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface)
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(TriggerInterface);
	
	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->FindOverlapActors(Actors, LevelTriggerInterfaceSpace);
	}
}