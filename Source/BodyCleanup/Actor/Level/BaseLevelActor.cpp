// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelActor.h"
#include "../../Components/LevelComponent.h"

#if WITH_EDITOR
#include "Engine/Level.h"
#include "Editor/UnrealEd/Public/UnrealEd.h"
#include "Editor/UnrealEd/Public/UnrealEdGlobals.h"
#include "Engine/Classes/Components/LineBatchComponent.h"
#include "Engine/Classes/Engine/Selection.h"
#endif // WITH_EDITOR

ABaseLevelActor::ABaseLevelActor()
{
	LevelComponent = CreateDefaultSubobject<ULevelComponent>(TEXT("LevelComponent"));

#if WITH_EDITORONLY_DATA
	LineBatchComponent = CreateEditorOnlyDefaultSubobject<ULineBatchComponent>(TEXT("SpawnPoint LinkLine"));
	if (LineBatchComponent)
	{
		LineBatchComponent->SetupAttachment(RootComponent);
		LineBatchComponent->SetHiddenInGame(true);
		LineBatchComponent->SetIsVisualizationComponent(true);
	}

	//USelection::SelectionChangedEvent.AddUObject(this, &APGSpawnTrigger::OnChangeSelectObject);
#endif // WITH_EDITORONLY_DATA
}