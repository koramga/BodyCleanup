// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSuckingActor.h"
#include "../../Components/Interactive/Classes/InteractiveSuckingComponent.h"

ACharacterSuckingActor::ACharacterSuckingActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	InteractiveSuckingComponent = CreateDefaultSubobject<UInteractiveSuckingComponent>("SuckingComponent");

	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ACharacterSuckingActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetSimulatePhysics(false);
	InitialLocation = GetActorLocation();
}

void ACharacterSuckingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
