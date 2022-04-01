// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGuardianController.h"


// Sets default values
ABaseGuardianController::ABaseGuardianController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TeamType = ETeamType::Enemy;
}

// Called when the game starts or when spawned
void ABaseGuardianController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGuardianController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGuardianController::InitializeBlackboardData()
{
	Super::InitializeBlackboardData();
}

void ABaseGuardianController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABaseGuardianController::OnUnPossess()
{
	Super::OnUnPossess();
}