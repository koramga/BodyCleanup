// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRagdollActor.h"

ABaseRagdollActor::ABaseRagdollActor()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
}

void ABaseRagdollActor::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(SkeletalMeshComponent))
	{
		UpdateDeath(true);
	}
}

void ABaseRagdollActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRagdollActor::UpdateDeath(bool bInIsDeath)
{
	Super::UpdateDeath(bInIsDeath);

	if (true == bInIsDeath)
	{
		SkeletalMeshComponent->SetCollisionProfileName(TEXT("Ragdoll"));
		SkeletalMeshComponent->SetSimulatePhysics(true);
	}
}
