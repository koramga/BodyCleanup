// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerSceneComponent.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"
#include "GameFramework/GameModeBase.h"

// Sets default values for this component's properties
UTriggerSceneComponent::UTriggerSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	LevelTriggerSettings.LevelTriggerWayType = ELevelTriggerWayType::OneWay;
	// ...
}


// Called when the game starts
void UTriggerSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetupTrigger();

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();

	if (GameModeBase->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
	{
		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GameModeBase);

		if (nullptr != LevelToolsGameModeBase)
		{
			LevelToolsGameModeBase->RegisterTrigger(this);
		}
	}
}

void UTriggerSceneComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UWorld* World = GetWorld();

	if (IsValid(World))
	{
		if (EEndPlayReason::Type::Destroyed == EndPlayReason)
		{
			AGameModeBase* GameModeBase = World->GetAuthGameMode();

			if (GameModeBase->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
			{
				ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GameModeBase);

				if (nullptr != LevelToolsGameModeBase)
				{
					LevelToolsGameModeBase->UnRegisterTrigger(this);
				}
			}
		}
	}
}

void UTriggerSceneComponent::SetupTrigger()
{
}


// Called every frame
void UTriggerSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTriggerSceneComponent::GetTriggerLocation(TArray<FVector>& TriggerLocations)
{
	TArray<TSoftObjectPtr<UActorComponent>> TriggerComponents;

	ULevelSupportFunctionLibrary::FindTriggerComponentFromLevelTriggerInput(TriggerComponents, this);

	for (TSoftObjectPtr<UActorComponent>& ActorComponent : TriggerComponents)
	{
		USceneComponent* SceneComponent = Cast<USceneComponent>(ActorComponent.Get());

		if (IsValid(SceneComponent))
		{
			TriggerLocations.Add(SceneComponent->GetComponentTransform().GetLocation());
		}
		else
		{
			TriggerLocations.Add(GetOwner()->GetActorLocation());
		}
	}
}

void UTriggerSceneComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	LevelTriggerUpdateParam = InputLevelTriggerUpdateParam;
}

const FLevelTriggerInputFrom* UTriggerSceneComponent::GetLevelTriggerInputFrom() const
{
	return &LevelTriggerInputFrom;
}

bool UTriggerSceneComponent::IsOnTrigger() const
{
	return LevelTriggerUpdateParam.bIsOnTrigger;
}

const FLevelTriggerSettings& UTriggerSceneComponent::GetLevelTriggerSettings() const
{
	return LevelTriggerSettings;
}