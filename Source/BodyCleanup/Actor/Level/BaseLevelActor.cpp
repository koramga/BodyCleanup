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
#include "DrawDebugHelpers.h"

ABaseLevelActor::ABaseLevelActor()
{
	LevelComponent = CreateDefaultSubobject<ULevelComponent>(TEXT("LevelComponent"));

//#if WITH_EDITORONLY_DATA
//	LineBatchComponent = CreateEditorOnlyDefaultSubobject<ULineBatchComponent>(TEXT("SpawnPoint LinkLine"));
//	if (LineBatchComponent)
//	{
//		LineBatchComponent->SetupAttachment(RootComponent);
//		LineBatchComponent->SetHiddenInGame(true);
//		LineBatchComponent->SetIsVisualizationComponent(true);
//	}
//
//	//USelection::SelectionChangedEvent.AddUObject(this, &APGSpawnTrigger::OnChangeSelectObject);
//#endif // WITH_EDITORONLY_DATA
}

void ABaseLevelActor::BeginPlay()
{
	Super::BeginPlay();	
}

void ABaseLevelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//LineBatchComponent->Flush();
	//
	//
	//
	//LineBatchComponent->DrawLine(GetActorLocation(), FVector(0.f, 0.f, 0.f), FLinearColor::Black, 10, 5.f, 10.f);
}
