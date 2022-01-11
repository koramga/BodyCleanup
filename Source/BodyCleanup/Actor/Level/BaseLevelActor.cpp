// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelActor.h"
#include "../../Components/LevelComponent.h"
#include "../../Components/ParentMovementComponent.h"
#include "../../Components/WarpComponent.h"
#include "../../Components/MarkupComponent.h"

#if WITH_EDITOR
#include "Engine/Level.h"
#include "Editor/UnrealEd/Public/UnrealEd.h"
#include "Editor/UnrealEd/Public/UnrealEdGlobals.h"
#include "Engine/Classes/Engine/Selection.h"
#endif // WITH_EDITOR
#include "DrawDebugHelpers.h"

ABaseLevelActor::ABaseLevelActor()
{
	LevelComponent = CreateDefaultSubobject<ULevelComponent>(TEXT("LevelComponent"));

#if WITH_EDITORONLY_DATA
//	LineBatchComponent = CreateEditorOnlyDefaultSubobject<ULineBatchComponent>(TEXT("SpawnPoint LinkLine"));
//	if (LineBatchComponent)
//	{
//		LineBatchComponent->SetupAttachment(RootComponent);
//		LineBatchComponent->SetHiddenInGame(true);
//		LineBatchComponent->SetIsVisualizationComponent(true);
//	}

	USelection::SelectionChangedEvent.AddUObject(this, &ABaseLevelActor::OnChangeSelectObject);
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

void ABaseLevelActor::OnChangeSelectObject(UObject* SelectionObj)
{
	if (false == IsValid(SelectionObj))
	{
		UE_LOG(LogTemp, Display, TEXT("SelectionObj is nullptr"));
		return;
	}

	USelection* Selection = Cast<USelection>(SelectionObj);

	if (false == IsValid(Selection))
		return;

	bIsSelected = Selection->IsSelected(this);
	DisplayLinkConnection(bIsSelected);
}

void ABaseLevelActor::DisplayLinkConnection(bool bShow)
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	if (bShow)
	{
		UE_LOG(LogTemp, Display, TEXT("DrawLinkConnect True : <%s>"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("DrawLinkConnect False : <%s>"), *GetName());
	}

	ULineBatchComponent* LineBatchComponent = GetWorld()->PersistentLineBatcher;

	if (IsValid(LineBatchComponent))
	{
		if (bShow)
		{
			LineBatchComponent->Flush();

			TArray<FBatchedLine> BatchLines;

			GetComponentByLinkConnect(GetRootComponent(), BatchLines);

			LineBatchComponent->DrawLines(BatchLines);

			//GetComponents();

			//UE_LOG(LogTemp, Display, TEXT("DrawLines")); 
			//
			//LineBatchComponent->DrawLine(GetActorLocation(), FVector(0.f, 0.f, 0.f), FColor::Red, 0, 2.f, 0.f);
		}
	}
}

#endif

void ABaseLevelActor::GetComponentByLinkConnect(USceneComponent* SceneComponent, TArray<FBatchedLine>& BatchLines)
{
	if (SceneComponent->IsA(UParentMovementComponent::StaticClass()))
	{
		UParentMovementComponent* ParentMovementComponent = Cast<UParentMovementComponent>(SceneComponent);

		if (IsValid(ParentMovementComponent))
		{
			const TArray<TSoftObjectPtr<ABaseActor>>& InteractiveActors = ParentMovementComponent->GetInteractiveActors();

			for (TSoftObjectPtr<ABaseActor> InteractiveActor : InteractiveActors)
			{
				if (IsValid(InteractiveActor.Get()))
				{
					BatchLines.Add(FBatchedLine(GetActorLocation(), InteractiveActor->GetActorLocation(), LineColor, 0.f, 2.f, 0));
				}
			}
		}
	}
	else if (SceneComponent->IsA(UWarpComponent::StaticClass()))
	{
		UWarpComponent* WarpComponent = Cast<UWarpComponent>(SceneComponent);

		if (IsValid(WarpComponent))
		{
			if (EWarpType::Point == WarpComponent->GetWarpType())
			{
				TSoftObjectPtr<class ABaseActor> WarpBaseActor = WarpComponent->GetWarpActor();

				if (WarpBaseActor.IsValid())
				{
					TSoftObjectPtr<class UMarkupComponent> MarkupComponent = WarpComponent->FindMarkupComponent();

					FVector Location = WarpBaseActor->GetActorLocation();

					if (MarkupComponent.IsValid())
					{
						Location = MarkupComponent->GetComponentToWorld().GetLocation();
					}

					BatchLines.Add(FBatchedLine(GetActorLocation(), Location, LineColor, 0.f, 2.f, 0));
				}
			}
		}
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		GetComponentByLinkConnect(ChildComponent, BatchLines);
	}
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
