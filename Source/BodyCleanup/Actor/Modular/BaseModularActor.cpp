// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseModularActor.h"
#include "Components/BoxComponent.h"


// Sets default values
ABaseModularActor::ABaseModularActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseModularActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseModularActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

