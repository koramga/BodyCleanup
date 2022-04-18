// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelActor.h"
#include "../../Components/Actor/LevelComponent.h"
//#include "../../Components/Actions/WarpComponent.h"
#include "LevelDesignerTools/Trigger/Classes/Scene/WarpComponent.h"
#include "LevelDesignerTools/Markup/Classes/MarkupComponent.h"
#include "LevelDesignerTools/Trigger/Classes/Scene/SpawnComponent.h"

#if WITH_EDITOR
#include "Engine/Level.h"
#include "Editor/UnrealEd/Public/UnrealEd.h"
#include "Editor/UnrealEd/Public/UnrealEdGlobals.h"
#include "Engine/Classes/Engine/Selection.h"
#endif // WITH_EDITOR
#include "DrawDebugHelpers.h"
//#include "../../Components/Interfaces/LevelTriggerInterface.h"
#include "LevelDesignerTools/Trigger/Interfaces/LevelTriggerInterface.h"

ABaseLevelActor::ABaseLevelActor()
{
	LevelComponent = CreateDefaultSubobject<ULevelComponent>(TEXT("LevelComponent"));

#if WITH_EDITORONLY_DATA
	//USelection::SelectionChangedEvent.AddUObject(this, &ABaseLevelActor::OnChangeSelectObject);
#endif // WITH_EDITORONLY_DATA
}

#if WITH_EDITOR

void ABaseLevelActor::PreEditChange(FProperty* PropertyThatWillChange)
{
	Super::PreEditChange(PropertyThatWillChange);
}

void ABaseLevelActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void ABaseLevelActor::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);

	if (bFinished)
	{
		DisplayLinkConnection(bIsSelected);
	}
}

//void ABaseLevelActor::OnChangeSelectObject(UObject* SelectionObj)
//{
//	if (false == IsValid(SelectionObj))
//	{
//		UE_LOG(LogTemp, Display, TEXT("SelectionObj is nullptr"));
//		return;
//	}
//
//	USelection* Selection = Cast<USelection>(SelectionObj);
//
//	if (false == IsValid(Selection))
//		return;
//
//	bIsSelected = Selection->IsSelected(this);
//	DisplayLinkConnection(bIsSelected);
//}

void ABaseLevelActor::DisplayLinkConnection(bool bShow)
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	ULineBatchComponent* LineBatchComponent = GetWorld()->PersistentLineBatcher;

	if (IsValid(LineBatchComponent))
	{
		if (bShow)
		{
			LineBatchComponent->Flush();

			TArray<FBatchedLine> BatchLines;

			

			GetComponentByLinkConnect(BatchLines);

			LineBatchComponent->DrawLines(BatchLines);
		}
	}
}

void ABaseLevelActor::GetComponentByLinkConnect(TArray<FBatchedLine>& BatchLines)
{
	const TSet<UActorComponent*>& ActorComponents = GetComponents();

	for (UActorComponent* ActorComponent : ActorComponents)
	{
		if(ActorComponent->IsA(USceneComponent::StaticClass()))
		{
			USceneComponent* SceneComponent = Cast<USceneComponent>(ActorComponent); 

			if (SceneComponent->IsA(UWarpComponent::StaticClass()))
			{
				FVector WarpLocation = Cast<UWarpComponent>(SceneComponent)->GetWarpLocation();

				BatchLines.Add(FBatchedLine(GetActorLocation(), WarpLocation, FColor::Blue, 0.f, 2.f, 0));
			}
			else if (SceneComponent->IsA(USpawnComponent::StaticClass()))
			{
				TArray<FVector> AffectLocations;

				Cast<USpawnComponent>(SceneComponent)->GetAffectPoints(AffectLocations);

				for (const FVector& Location : AffectLocations)
				{
					BatchLines.Add(FBatchedLine(GetActorLocation(), Location, FColor::Blue, 0.f, 2.f, 0));
				}
			}
		}


		if (ActorComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass()))
		{
			TArray<FVector> TriggerLocations;

			Cast<ILevelTriggerInterface>(ActorComponent)->GetTriggerLocation(TriggerLocations);

			for (const FVector& Location : TriggerLocations)
			{
				BatchLines.Add(FBatchedLine(GetActorLocation(), Location, FColor::Red, 0.f, 2.f, 0));
			}
		}

		//TArray<USceneComponent*> ChildrenComponents;
		//
		//SceneComponent->GetChildrenComponents(false, ChildrenComponents);
		//
		//for (USceneComponent* ChildComponent : ChildrenComponents)
		//{
		//	GetComponentByLinkConnect(ChildComponent, BatchLines);
		//}
	}

}

#endif

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
