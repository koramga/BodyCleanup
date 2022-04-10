// Fill out your copyright notice in the Description page of Project Settings.


#include "HitComponentTriggerComponent.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"

UHitComponentTriggerComponent::UHitComponentTriggerComponent()
{
	LevelTriggerSettings.TriggerPrimitiveComponentEventType = ETriggerPrimitiveComponentEventType::Hit;
}

void UHitComponentTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHitComponentTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UHitComponentTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
}

bool UHitComponentTriggerComponent::IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult)
{
	if(false == Super::IsApplyTriggerFromPrimitiveComopnent(OtherPrimitiveComponent, OtherActor, SweepResult))
	{
		return false;
	}

	return true;
	//return OtherPrimitiveComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass());
}
