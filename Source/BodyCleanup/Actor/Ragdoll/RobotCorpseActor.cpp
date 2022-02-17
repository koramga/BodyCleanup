// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCorpseActor.h"
#include "../../Components/Interactive/Classes/InteractiveSuckingComponent.h"

ARobotCorpseActor::ARobotCorpseActor()
{
	InteractiveSuckingComponent = CreateDefaultSubobject<UInteractiveSuckingComponent>(TEXT("InteractiveSuckingComponent"));
}

void ARobotCorpseActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARobotCorpseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARobotCorpseActor::UpdateDeath(bool bInIsDeath)
{
	Super::UpdateDeath(bInIsDeath);
}
