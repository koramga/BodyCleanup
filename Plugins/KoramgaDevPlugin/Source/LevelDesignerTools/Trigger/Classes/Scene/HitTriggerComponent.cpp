// Fill out your copyright notice in the Description page of Project Settings.


#include "HitTriggerComponent.h"
#include "../../../Utility/LevelSupportFunctionLibrary.h"

UHitTriggerComponent::UHitTriggerComponent()
{
	LevelTriggerSettings.TriggerPrimitiveComponentEventType = ETriggerPrimitiveComponentEventType::Hit;
}

void UHitTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHitTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UHitTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
}

bool UHitTriggerComponent::IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult)
{
	if(false == Super::IsApplyTriggerFromPrimitiveComopnent(OtherPrimitiveComponent, OtherActor, SweepResult))
	{
		return false;
	}

	return true;
	//return OtherPrimitiveComponent->GetClass()->ImplementsInterface(ULevelTriggerInterface::StaticClass());
}
