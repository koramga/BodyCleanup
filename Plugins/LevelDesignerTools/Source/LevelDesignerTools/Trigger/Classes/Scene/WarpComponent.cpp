// Fill out your copyright notice in the Description page of Project Settings.


#include "WarpComponent.h"
//#include "../MarkupComponent.h"
#include "../../../Markup/Interfaces/LevelMarkupInterface.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"

// Sets default values for this component's properties
UWarpComponent::UWarpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWarpComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UWarpComponent::SetupTrigger()
{
	if (EWarpType::Location == WarpType)
	{
		MarkupComponent = Cast<UObject>(FindMarkupComponent());
	}
}

void UWarpComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	if (EWarpType::Location == WarpType)
	{
		if (InputLevelTriggerUpdateParam.bIsOnTrigger)
		{
			//반응하면 됩니다.
			TArray<TSoftObjectPtr<AActor>> Actors;
	
			if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
			{
				ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());
	
				if (nullptr != LevelToolsGameModeBase)
				{
					const ULevelTriggerManager* LevelTriggerManager = LevelToolsGameModeBase->GetLevelTriggerManager();
	
					if (IsValid(LevelTriggerManager))
					{
						LevelTriggerManager->FindOverlapActors(Actors, this);
					}
				}
			}
	
			if (Actors.Num() > 0)
			{
				FVector Location = GetOwner()->GetActorLocation();
	
				if (WarpActor.IsValid())
				{
					Location = WarpActor->GetActorLocation();
				}
	
				if (MarkupComponent.IsValid())
				{
					Location = Cast<ILevelMarkupInterface>(MarkupComponent.Get())->GetMarkupLocation();
				}
	
				for (TSoftObjectPtr<AActor> Actor : Actors)
				{
					Actor->SetActorLocation(Location);
				}
			}
		}
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
}

EWarpType UWarpComponent::GetWarpType() const
{
	return WarpType;
}

TSoftObjectPtr<AActor> UWarpComponent::GetWarpActor() const
{
	return WarpActor;
}

ILevelMarkupInterface* UWarpComponent::FindMarkupComponent() const
{
	if (false == MarkupName.IsNone())
	{
		if (EWarpType::Location == WarpType)
		{
			if (WarpActor.IsValid())
			{
				if (false == MarkupName.IsNone())
				{
					return ULevelSupportFunctionLibrary::FindMarkupInterfaceByName(WarpActor.Get(), MarkupName);
				}
			}
			else
			{
				return ULevelSupportFunctionLibrary::FindMarkupInterfaceByName(GetOwner(), MarkupName);
			}
		}
	}

	return nullptr;
}

FVector UWarpComponent::GetWarpLocation() const
{
	AActor* StdActor = GetOwner();

	if (WarpActor.IsValid())
	{
		StdActor = WarpActor.Get();
	}
	
	if (false == MarkupName.IsNone())
	{
		ILevelMarkupInterface* LevelMarkupInterface = FindMarkupComponent();
	
		if (nullptr != LevelMarkupInterface)
		{
			return LevelMarkupInterface->GetMarkupLocation();
		}		
	}

	return StdActor->GetActorLocation();
}