// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActorSettingsComponent.h"
#include "../../GAS/Interface/Actor/GASActor.h"

// Sets default values for this component's properties
UGameActorSettingsComponent::UGameActorSettingsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	WeightType = EWeightType::None;
}


// Called when the game starts
void UGameActorSettingsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Owner = GetOwner();

	if(IsValid(Owner))
	{
		if(Owner->IsA(UGASActor::StaticClass()))
		{
			IGASActor* GASActor = Cast<IGASActor>(Owner);

			for(const TSubclassOf<class UBaseAttributeSet>& BaseAttributeSetClass : BaseAttributeSetClasses)
			{
				GASActor->AddAttributeSet(BaseAttributeSetClass);
			}
		}
	}
}


// Called every frame
void UGameActorSettingsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EWeightType UGameActorSettingsComponent::GetWeightType() const
{
	return WeightType;
}

void UGameActorSettingsComponent::SetWeightType(EWeightType InputWeightType)
{
	WeightType = InputWeightType;
}

