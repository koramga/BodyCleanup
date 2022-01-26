// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActorComponent.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"
#include "GameFramework/GameModeBase.h"

// Sets default values for this component's properties
UTriggerActorComponent::UTriggerActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	LevelTriggerSettings.LevelTriggerWayType = ELevelTriggerWayType::TwoWay;
	LevelTriggerSettings.TriggerPrimitiveComponentEventType = ETriggerPrimitiveComponentEventType::Overlap;
	// ...
}


// Called when the game starts
void UTriggerActorComponent::BeginPlay()
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

void UTriggerActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
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

void UTriggerActorComponent::SetupTrigger()
{
}

void UTriggerActorComponent::UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam)
{
}

bool UTriggerActorComponent::IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult)
{
	return true;
}


// Called every frame
void UTriggerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTriggerActorComponent::GetTriggerLocation(TArray<FVector>& TriggerLocations)
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

void UTriggerActorComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	LevelTriggerUpdateParam = InputLevelTriggerUpdateParam;
}

const FLevelTriggerInputFrom* UTriggerActorComponent::GetLevelTriggerInputFrom() const
{
	return &LevelTriggerInputFrom;
}

bool UTriggerActorComponent::IsOnTrigger() const
{
	return LevelTriggerUpdateParam.bIsOnTrigger;
}

const FLevelTriggerSettings& UTriggerActorComponent::GetLevelTriggerSettings() const
{
	return LevelTriggerSettings;
}
