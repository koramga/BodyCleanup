// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerManager.h"

void ULevelTriggerInterfaceSpace::AddTriggerComponents(TSoftObjectPtr<UObject>& InputTriggerComponent)
{
	TriggerComponents.Add(InputTriggerComponent);

	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(InputTriggerComponent.Get());

	if (IsValid(PrimitiveComponent))
	{
		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapBegin);
		PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &ULevelTriggerInterfaceSpace::__OnTriggerComponentOverlapEnd);
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
			if (TriggerOnComponents.Num() != TriggerComponents.Num())
			{
				bIsOnTrigger = bInputIsOnTrigger;
				UpdateTrigger(bIsOnTrigger);
			}
		}
	}
}

void ULevelTriggerManager::AddTriggerInterface(const TSoftObjectPtr<ILevelTriggerInterface>& TriggerInterface)
{
	TUniquePtr<ULevelTriggerInterfaceSpace>* LevelTriggerInterfaceSpace = LevelTriggerInterfaces.Find(TriggerInterface);
	
	if (nullptr == LevelTriggerInterfaceSpace)
	{
		TUniquePtr<ULevelTriggerInterfaceSpace> LevelTriggerInterfaceSpace = TUniquePtr<ULevelTriggerInterfaceSpace>(NewObject<ULevelTriggerInterfaceSpace>(this));

		LevelTriggerInterfaces.Add(TriggerInterface, TUniquePtr<ULevelTriggerInterfaceSpace>());
	}
}