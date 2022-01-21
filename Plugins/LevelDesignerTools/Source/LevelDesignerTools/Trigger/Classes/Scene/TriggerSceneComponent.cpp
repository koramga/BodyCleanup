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
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();

	if (GameModeBase->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
	{
		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GameModeBase);

		if (nullptr != LevelToolsGameModeBase)
		{
			LevelToolsGameModeBase->RegisterTrigger(this);
		}
	}
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
}

const FLevelTriggerInput* UTriggerSceneComponent::GetLevelTriggerInput() const
{
	return &LevelTriggerInput;
}

