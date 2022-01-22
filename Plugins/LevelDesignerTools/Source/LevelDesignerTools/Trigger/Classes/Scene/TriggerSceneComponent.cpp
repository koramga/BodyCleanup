// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerSceneComponent.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"
#include "GameFramework/GameModeBase.h"

// Sets default values for this component's properties
UTriggerSceneComponent::UTriggerSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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
}

void UTriggerSceneComponent::UpdateTrigger(bool bInputIsOnTrigger)
{
	bIsOnTrigger = bInputIsOnTrigger;
}

const FLevelTriggerInputFrom* UTriggerSceneComponent::GetLevelTriggerInputFrom() const
{
	return &LevelTriggerInputFrom;
}

bool UTriggerSceneComponent::IsOnTrigger() const
{
	return bIsOnTrigger;
}

