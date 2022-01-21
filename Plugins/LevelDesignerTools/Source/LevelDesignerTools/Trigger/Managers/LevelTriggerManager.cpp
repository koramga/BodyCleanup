// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerManager.h"
#include "../../Utility/LevelSupportFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void ULevelTriggerInterfaceSpace::Initialize()
{
	ULevelSupportFunctionLibrary::FindTriggerComponentFromLevelTriggerInput(TriggerComponents, Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get()));
	
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

void ULevelTriggerInterfaceSpace::SetLevelTriggerInterface(ILevelTriggerInterface* InputLevelTriggerInterface)
{
	LevelTriggerInterface = Cast<ULevelTriggerInterface>(InputLevelTriggerInterface);
}

void ULevelTriggerInterfaceSpace::SetLevelTriggerManager(const TSoftObjectPtr<ULevelTriggerManager>& InputLevelTriggerManager)
{
	LevelTriggerManager = InputLevelTriggerManager;
}

void ULevelTriggerInterfaceSpace::UpdateTrigger(bool bInputIsOnTrigger)
{
	ILevelTriggerInterface* UpdateLevelTriggerInterface = Cast<ILevelTriggerInterface>(LevelTriggerInterface.Get());

	const FLevelTriggerInput* LevelTriggerInput = UpdateLevelTriggerInterface->GetLevelTriggerInput();

	if (false == bIsOnTrigger)
	{
		if (true == bInputIsOnTrigger)
		{
			bIsOnTrigger = true;
			UpdateLevelTriggerInterface->UpdateTrigger(bInputIsOnTrigger);
		}
	}
	else
	{
		UpdateLevelTriggerInterface->UpdateTrigger(bInputIsOnTrigger);
	}
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
	const FLevelTriggerInput* ParamLevelTriggerInput = Cast<ILevelTriggerInterface>(LevelTriggerInterfaceSpace->LevelTriggerInterface.Get())->GetLevelTriggerInput();
	
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
	
			ULevelTriggerInterfaceSpace* ParamLevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(ParamLevelTriggerInterface);
			
			if (nullptr != LevelTriggerInterfaceSpace)
			{
				FindOverlapActors(Actors, LevelTriggerInterfaceSpace);
			}
		}
	}
}

const ILevelTriggerInterface* ULevelTriggerInterfaceSpace::GetLevelTriggerInterface() const
{
	return Cast< const ILevelTriggerInterface>(LevelTriggerInterface.Get());
}

ULevelTriggerInterfaceSpace* ULevelTriggerManager::GetLevelTriggerInterfaceSpace(ILevelTriggerInterface* TriggerInterface)
{
	if (nullptr == TriggerInterface)
	{
		return nullptr;
	}

	ULevelTriggerInterfaceSpace* LevelTriggerInterface = LevelTriggerInterfaces.FindRef(Cast<ULevelTriggerInterface>(TriggerInterface));

	if (nullptr == LevelTriggerInterface)
	{
		LevelTriggerInterface = Cast<ULevelTriggerInterfaceSpace>(NewObject<ULevelTriggerInterfaceSpace>(this));

		LevelTriggerInterface->SetLevelTriggerManager(this);
		LevelTriggerInterface->SetLevelTriggerInterface(TriggerInterface);

		LevelTriggerInterfaces.Add(Cast<ULevelTriggerInterface>(TriggerInterface), LevelTriggerInterface);
	}

	return LevelTriggerInterface;
}

ULevelTriggerInterfaceSpace* ULevelTriggerManager::GetLevelTriggerInterfaceSpace(ULevelTriggerInterface* TriggerInterface)
{
	return GetLevelTriggerInterfaceSpace(Cast<ILevelTriggerInterface>(TriggerInterface));
}

void ULevelTriggerManager::InitializeTriggerInterfaceSpace(ILevelTriggerInterface* TriggerInterface)
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(TriggerInterface);
	
	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->Initialize();
	}
}

void ULevelTriggerManager::FindOverlapActors(TArray<TSoftObjectPtr<AActor>>& Actors, ILevelTriggerInterface* TriggerInterface)
{
	ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = GetLevelTriggerInterfaceSpace(TriggerInterface);
	
	if (IsValid(LevelTriggerInterfaceSpace))
	{
		LevelTriggerInterfaceSpace->FindOverlapActors(Actors, LevelTriggerInterfaceSpace);
	}
}

void ULevelTriggerManager::BeginPlay()
{

}