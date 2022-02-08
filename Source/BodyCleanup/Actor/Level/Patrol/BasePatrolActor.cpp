// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePatrolActor.h"
#include "Components/BoxComponent.h"
#include "../../../Components/Actor/LevelComponent.h"

ABasePatrolActor::ABasePatrolActor()
{
	if(IsValid(LevelComponent))
	{
		LevelComponent->SetLevelType(ELevelType::Patrol);	
	}

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetupAttachment(RootComponent);
}

void ABasePatrolActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePatrolActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool ABasePatrolActor::IsGoal(const AActor* InActor) const
{
	TArray<AActor*> OutOverlappingActors;
	
	BoxComponent->GetOverlappingActors(OutOverlappingActors, InActor->GetClass());

	for(AActor* Actor : OutOverlappingActors)
	{
		if(Actor == InActor)
		{
			return true;
		}
	}

	return false;
}

FVector ABasePatrolActor::GetGoalPosition() const
{
	return GetActorLocation();
}
